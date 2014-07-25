/*!
 * AsyncMediatorCall.h
 * mediator_test
 *
 * Created by Lansdon Page on 5/25/14.
 * Copyright (c) 2014 Lansdon Page. All rights reserved.
 */

#ifndef __mediator_test__AsyncMediatorCall__
#define __mediator_test__AsyncMediatorCall__

#include <iostream>
#include "MediatorKeys.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include <QObject>
#include "asyncmediatorworker.h"

//namespace drc {
//namespace drc_shared {

/*!
 * \brief The AsyncMediatorCall class
 */
class AsyncMediatorCall : QObject
{
    Q_OBJECT

public:
    /*!
     * \brief AsyncMediatorCall
     * \param sendEventMediatorKey
     * \param recieveEventMediatorKey
     * \param callback
     * \param argObject
     * \param waitForResponse
     * \param timeoutSecs
     */
    AsyncMediatorCall(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, void* argObject, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    /*!
     * \brief AsyncMediatorCall
     * \param sendEventMediatorKey
     * \param recieveEventMediatorKey
     * \param callback
     * \param _sendMediatorArg
     * \param waitForResponse
     * \param timeoutSecs
     */
    AsyncMediatorCall(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, MediatorArg _sendMediatorArg, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    virtual ~AsyncMediatorCall();

    /// Accessors
    /*!
     * \brief GetMediatorArg
     * \return
     */
    MediatorArg& GetMediatorArg() { return _sendMediatorArg; }
    /// This will perform the send event, and wait for the response.
    /*!
     * \brief Send
     */
    void Send();

private:
    // Settings - This list of parameters is saved, and passed to each new thread when they are spawned.
	QString _sendEventMediatorKey;		// Send Event Key
	QString _recieveEventMediatorKey;	// Listen for this result Key
    MediatorCallbackFunc _callback;			// This is called when a response is received.
    MediatorArg _sendMediatorArg;			// This is the argument being sent.
    MediatorArg _recieveMediatorArg;        // This is the argument being recieved.
    bool _willWaitForResponse;              // Turn this on when you want to handle a response event.
    unsigned long _timeoutSecs;             // How long before we stop waiting for a response

    bool _waiting;                          // This will block additional calls to Send() if a Send is already in progress.

public slots:
    /*!
     * \brief errorString
     * \param error
     */
    void errorString(QString error);        // meh. this can prolly go away.
    /*!
     * \brief threadFinished
     */
    void threadFinished();
    /*!
     * \brief DoCallbackOnMainThread
     */
    void DoCallbackOnMainThread();
    /*!
     * \brief updateRecieveArg
     * \param responseArg
     */
    void updateRecieveArg(MediatorArg responseArg);
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif /* defined(__mediator_test__AsyncMediatorCall__) */
