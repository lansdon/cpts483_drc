//
//  AsyncMediatorCall.cpp
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//

#include "AsyncMediatorCall.h"
#include <iostream>
#include "MediatorKeys.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include <thread>
#include <future>

//namespace drc {
//namespace drc_shared {

AsyncMediatorCall::AsyncMediatorCall(
	std::string sendEventMediatorKey, 
	std::string recieveEventMediatorKey, 
	MediatorCallback callback, 
	void* argObject, 
	unsigned long timeoutSecs)
: _sendEventMediatorKey(sendEventMediatorKey)
, _recieveEventMediatorKey(recieveEventMediatorKey)
, _callback(callback)
, _mediatorArg(MediatorArg(argObject))
, _timeoutSecs(timeoutSecs)
, _waiting(false)
{
	Mediator::Register(_recieveEventMediatorKey, [this](MediatorArg mediatorArg) { ResponseRecieved(mediatorArg); });		// Start listening for a response
}

AsyncMediatorCall::AsyncMediatorCall(
	std::string sendEventMediatorKey,
	std::string recieveEventMediatorKey,
	MediatorCallback callback,
	MediatorArg mediatorArg,
	unsigned long timeoutSecs)
	: _sendEventMediatorKey(sendEventMediatorKey)
	, _recieveEventMediatorKey(recieveEventMediatorKey)
	, _callback(callback)
	, _mediatorArg(mediatorArg)
	, _timeoutSecs(timeoutSecs)
	, _waiting(false)
{
	Mediator::Register(_recieveEventMediatorKey, [this](MediatorArg mediatorArg) { ResponseRecieved(mediatorArg); });		// Start listening for a response

}

AsyncMediatorCall::~AsyncMediatorCall() 
{
}



void AsyncMediatorCall::Send()					// This will perform the send event, and wait for the response.
{
	if (!_waiting)
	{
		_waiting = true;
		std::async(&AsyncMediatorCall::SendEvent, this);	// fire and forget seperate thread
	}
	else
	{
        std::cerr << "\n !!! A request is already in progress... Please try again later.\n";
	}
}

void AsyncMediatorCall::SendEvent()	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
{
	std::cout << "Async -> thread running...\n";

	_waitingAsync = std::async(&AsyncMediatorCall::WaitForResponse, this);
	Mediator::Call(_sendEventMediatorKey, _mediatorArg);
	bool responseSuccess = _waitingAsync.get();      // waits for response

	if (!responseSuccess)
		std::cerr << "Async -> Error waiting for response.\n";
}

double AsyncMediatorCall::Elapsed(clock_t startTime) {
	return double(clock() - startTime) / CLOCKS_PER_SEC;
}

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
void qSleep(int ms)
{
//    QTEST_ASSERT(ms > 0);
    if(ms <= 0) ms = 1;
#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
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
			return false;		// timeout = error
		}
	}
	return true;			// no error
}

void AsyncMediatorCall::ResponseRecieved(MediatorArg mediatorArg)	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
{
	// Internal cleanup and maintenance first
//	 _thread.join();											// All done with the thread.

	// Call the callback we were given
	 if (_callback)
		_callback(mediatorArg);

	// Ready to do it again
	_waiting = false;

	std::cout << "Async -> Response recieved - thread terminated.\n";
}

//}
//}
