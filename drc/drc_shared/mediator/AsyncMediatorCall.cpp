//
//  AsyncMediatorCall.cpp
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//


#include <iostream>
#include "MediatorKeys.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include "AsyncMediatorCall.h"
#include <QDebug>
#include <QObject>
#include <QThread>
#include "asyncmediatorworker.h"

//namespace drc {
//namespace drc_shared {

AsyncMediatorCall::AsyncMediatorCall(
    std::string sendEventMediatorKey,
    std::string recieveEventMediatorKey,
    MediatorCallbackFunc callback,
    void* argObject,
    bool waitForResponse,
    unsigned long timeoutSecs)
: QObject(0)
, _sendEventMediatorKey(sendEventMediatorKey)
, _recieveEventMediatorKey(recieveEventMediatorKey)
, _callback(callback)
, _sendMediatorArg(MediatorArg(argObject))
, _willWaitForResponse(sendEventMediatorKey.length() ?  waitForResponse : false)
, _timeoutSecs(timeoutSecs)
, _waiting(false)
{
    qRegisterMetaType<MediatorArg>("MediatorArg");
}

AsyncMediatorCall::AsyncMediatorCall(
    std::string sendEventMediatorKey,
    std::string recieveEventMediatorKey,
    MediatorCallbackFunc callback,
    MediatorArg mediatorArg,
    bool waitForResponse,
    unsigned long timeoutSecs)
: QObject(0)
, _sendEventMediatorKey(sendEventMediatorKey)
, _recieveEventMediatorKey(recieveEventMediatorKey)
, _callback(callback)
, _recieveMediatorArg(mediatorArg)
, _willWaitForResponse(sendEventMediatorKey.length() ?  waitForResponse : false)
, _timeoutSecs(timeoutSecs)
, _waiting(false)
{
}

AsyncMediatorCall::~AsyncMediatorCall()
{

}

void AsyncMediatorCall::Send()					// This will perform the send event, and wait for the response.
{
    if (!_waiting)
    {
        _waiting = true;

        // Create a thread, and run a worker class on it.
        // When the worker finishes, threadFinished() will be called.
        // Note: the worker handles all callbacks, timeouts and errors.
        QThread* thread = new QThread;
        AsyncMediatorWorker* worker = new AsyncMediatorWorker(
                    _sendEventMediatorKey,
                    _recieveEventMediatorKey,
                    _callback,
                    _sendMediatorArg,
                    _willWaitForResponse,
                    _timeoutSecs);
        worker->moveToThread(thread);
        connect(worker, SIGNAL(sendResponseArg(MediatorArg)), this, SLOT(updateRecieveArg(MediatorArg)));
        connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(thread, SIGNAL(started()), worker, SLOT(Start()));
        connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), this, SLOT(threadFinished()));
        thread->start();
    }
    else
    {
        qDebug() << "\n !!! A request is already in progress... Please try again later.";
    }
}

void AsyncMediatorCall::errorString(QString error)
{
    qDebug() << "Async Error: " << error;
}

void AsyncMediatorCall::threadFinished()
{
    // Invoke the callback function on the main thread.
    QMetaObject::invokeMethod(this, "DoCallbackOnMainThread", Qt::QueuedConnection);

    _waiting = false;
}

void AsyncMediatorCall::DoCallbackOnMainThread()
{
    if(_callback)
    {
        qDebug() << "Async -> Doing callback on main thread";
        _callback(_recieveMediatorArg);
    }
}

void AsyncMediatorCall::updateRecieveArg(MediatorArg responseArg)
{
    qDebug() << "Async -> updating recieved arg";
    _recieveMediatorArg = responseArg;
}

//}
//}
