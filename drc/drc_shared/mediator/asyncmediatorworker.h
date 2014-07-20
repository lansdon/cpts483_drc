#ifndef ASYNCMEDIATORWORKER_H
#define ASYNCMEDIATORWORKER_H

#include <QObject>
#include "MediatorArg.h"
#include "Mediator.h"
#include <ctime>

const unsigned long DEF_ASYNC_TIMEOUT_SECS = 5; // timeout in seconds


///
/// \brief The AsyncMediatorWorker class
///
/// This class handles sending a single mediator call (key)
/// and listens for a response. It's designed to work with
/// AsynchMediatorCall which launches workers on seperate threads.
///
/// *** Do not use this class directly! Use AsynchMediatorCall!

class AsyncMediatorWorker : public QObject {
    Q_OBJECT

public:
    AsyncMediatorWorker(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, void* argObject, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    AsyncMediatorWorker(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, MediatorArg sendMediatorArg, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    ~AsyncMediatorWorker();

public slots:
    void Start();
//    void DoCallbackOnMainThread();

signals:
    void finished();
    void error(QString err);
    void sendResponseArg(MediatorArg responseArg);

private:


    bool _waiting;						// This will block additional calls to Send() if a Send is already in progress.
    bool WaitForResponse();             // The loop handles timeouts while waiting

    QString _sendEventMediatorKey;		// Send Event Key
    QString _recieveEventMediatorKey;	// Listen for this result Key

    MediatorCallbackFunc _callback;			// NOT USED - Handled by AsynchMediatorCall

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
