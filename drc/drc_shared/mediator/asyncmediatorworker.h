#ifndef ASYNCMEDIATORWORKER_H
#define ASYNCMEDIATORWORKER_H

#include <QObject>
#include "MediatorArg.h"
#include "Mediator.h"
#include <ctime>

const unsigned long DEF_ASYNC_TIMEOUT_SECS = 10; // timeout in seconds

class AsyncMediatorWorker : public QObject {
    Q_OBJECT

public:
    AsyncMediatorWorker(std::string sendEventMediatorKey, std::string recieveEventMediatorKey, MediatorCallbackFunc callback, void* argObject, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    AsyncMediatorWorker(std::string sendEventMediatorKey, std::string recieveEventMediatorKey, MediatorCallbackFunc callback, MediatorArg sendMediatorArg, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    ~AsyncMediatorWorker();

public slots:
    void Start();
    void DoCallbackOnMainThread();

signals:
    void finished();
    void error(QString err);

private:


    bool _waiting;						// This will block additional calls to Send() if a Send is already in progress.
    bool WaitForResponse();             // The loop handles timeouts while waiting

    std::string _sendEventMediatorKey;		// Send Event Key
    std::string _recieveEventMediatorKey;	// Listen for this result Key

    MediatorCallbackFunc _callback;			// This is called when a response is received.


    MediatorArg _sendMediatorArg;			// This is the argument being sent.
    MediatorArg _recieveMediatorArg;        // This is the argument being recieved.
    // Internal mediator callbacks
    MediatorId ResponseRecievedId;

    double Elapsed(clock_t startTime);
    bool _willWaitForResponse;          // Turn this on when you want to handle a response event.
    void ResponseRecieved(MediatorArg mediatorArg);	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
    unsigned long _timeoutSecs;			// How long before we stop waiting for a response
};
#endif // ASYNCMEDIATORWORKER_H
