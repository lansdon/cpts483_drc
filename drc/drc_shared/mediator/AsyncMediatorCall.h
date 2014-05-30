//
//  AsyncMediatorCall.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//

#ifndef __mediator_test__AsyncMediatorCall__
#define __mediator_test__AsyncMediatorCall__

#include <iostream>
#include "MediatorKeys.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include <thread>
#include <future>
#include <QObject>

//namespace drc {
//namespace drc_shared {

const unsigned long DEF_ASYNC_TIMEOUT_SECS = 30; // timeout in seconds

class AsyncMediatorCall : QObject
{
    Q_OBJECT

public:
    AsyncMediatorCall(std::string sendEventMediatorKey, std::string recieveEventMediatorKey, MediatorCallbackFunc callback, void* argObject, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    AsyncMediatorCall(std::string sendEventMediatorKey, std::string recieveEventMediatorKey, MediatorCallbackFunc callback, MediatorArg _mediatorArg, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    virtual ~AsyncMediatorCall();

    // Accessors
    MediatorArg& GetMediatorArg() { return _mediatorArg; }

	void Send();						// This will perform the send event, and wait for the response.

private:
    // Internal mediator callbacks
    MediatorId ResponseRecievedId;

	std::string _sendEventMediatorKey;		// Send Event Key
	std::string _recieveEventMediatorKey;	// Listen for this result Key
    MediatorCallbackFunc _callback;			// This is called when a response is received.
	MediatorArg _mediatorArg;			// This is the argument being sent.


	unsigned long _timeoutSecs;			// How long before we stop waiting for a response
	std::future<bool> _waitingAsync;	// Dats why it's async!

    bool _willWaitForResponse;          // Turn this on when you want to handle a response event.
	bool WaitForResponse();
	bool _waiting;						// This will block additional calls to Send() if a Send is already in progress.

	void SendEvent();	// This is run on a seperate thread. This internal function handles maintenance when a event is sent. 
	void ResponseRecieved(MediatorArg mediatorArg);	// This internal function handles maintenance when a response is recieved. Then the _callback is called.

	double Elapsed(clock_t startTime);



public slots:
    void DoCallbackOnMainThread();

};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif /* defined(__mediator_test__AsyncMediatorCall__) */
