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
#include <thread>
#include <future>
#include <QDebug>
#include <QObject>

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
, _recieveMediatorArg(MediatorArg(argObject))
, _timeoutSecs(timeoutSecs)
, _willWaitForResponse(sendEventMediatorKey.length() ?  waitForResponse : false)
, _waiting(false)
{
    ResponseRecievedId = Mediator::Register(_recieveEventMediatorKey, [this](MediatorArg mediatorArg) { this->ResponseRecieved(mediatorArg); });		// Start listening for a response
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
, _timeoutSecs(timeoutSecs)
, _willWaitForResponse(sendEventMediatorKey.length() ?  waitForResponse : false)
, _waiting(false)
{
    ResponseRecievedId = Mediator::Register(_recieveEventMediatorKey, [this](MediatorArg mediatorArg) { this->ResponseRecieved(mediatorArg); });		// Start listening for a response
}

AsyncMediatorCall::~AsyncMediatorCall()
{

}

void AsyncMediatorCall::Send()					// This will perform the send event, and wait for the response.
{
	if (!_waiting)
	{
		_waiting = true;
        std::async(std::launch::async, &AsyncMediatorCall::SendEvent, this);	// fire and forget seperate thread
	}
	else
	{
        qDebug() << "\n !!! A request is already in progress... Please try again later.";
	}
}

void AsyncMediatorCall::SendEvent()	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
{
    qDebug() << "Async -> thread running...";


    _waitingAsync = std::async(std::launch::async, &AsyncMediatorCall::WaitForResponse, this);
    Mediator::Call(_sendEventMediatorKey, _sendMediatorArg);
    WaitForResponse();

	bool responseSuccess = _waitingAsync.get();      // waits for response

	if (!responseSuccess)
        qDebug() << "Async -> Error waiting for response.";
//    else qDebug() << "Async -> Complete";
}

double AsyncMediatorCall::Elapsed(clock_t startTime) {
	return double(clock() - startTime) / CLOCKS_PER_SEC;
}

// This will wait for the asynchronous response. This is intended to be run asynchronously
bool AsyncMediatorCall::WaitForResponse()
{
    clock_t startTime = clock();
    // Wait for a response, or timeout
    while (_waiting)
    {
        double elapsed = Elapsed(startTime);
        if (elapsed > _timeoutSecs)
        {
            _waiting = false;
            qDebug() << "Async -> Timeout";
            return false;		// timeout = error
        }
    }
//    qDebug() << "Async -> Done waiting";
    return true;			// no error
}


void AsyncMediatorCall::ResponseRecieved(MediatorArg mediatorArg)	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
{
    _recieveMediatorArg = mediatorArg;

    // Invoke the callback function on the main thread.
    if(_callback)
    {
        QMetaObject::invokeMethod(this, "DoCallbackOnMainThread", Qt::QueuedConnection);
    }

     qDebug() << "Async -> Response recieved - thread terminated.";

    // Ready to do it again
    _waiting = false;
}

void AsyncMediatorCall::DoCallbackOnMainThread()
{
    qDebug() << "Doing callback on main thread";
    _callback(_recieveMediatorArg);
}

//}
//}
