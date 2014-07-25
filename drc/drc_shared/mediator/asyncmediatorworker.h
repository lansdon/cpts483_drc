#ifndef ASYNCMEDIATORWORKER_H
#define ASYNCMEDIATORWORKER_H

#include <QObject>
#include "MediatorArg.h"
#include "Mediator.h"
#include <ctime>

const unsigned long DEF_ASYNC_TIMEOUT_SECS = 5; // timeout in seconds

/*!
 * \brief The AsyncMediatorWorker class.
 *  This class handles sending a single mediator call and listens
 *  for a response.
 *
 *  It's desinged to work with AsynchMediatorCall which launches workers
 *  on seperate threads.
 *  DO NOT use this class directly! USE AsyncMediatorCall!
 */
class AsyncMediatorWorker : public QObject {
    Q_OBJECT

public:
    AsyncMediatorWorker(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, void* argObject, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    AsyncMediatorWorker(QString sendEventMediatorKey, QString recieveEventMediatorKey, MediatorCallbackFunc callback, MediatorArg sendMediatorArg, bool waitForResponse = false, unsigned long timeoutSecs = DEF_ASYNC_TIMEOUT_SECS);
    ~AsyncMediatorWorker();

public slots:
    void Start();
//  void DoCallbackOnMainThread();

signals:
    /*!
     * \brief finished
     */
    void finished();
    /*!
     * \brief error
     * \param err
     */
    void error(QString err);
    /*!
     * \brief sendResponseArg
     * \param responseArg
     */
    void sendResponseArg(MediatorArg responseArg);

private:


    bool _waiting;						// This will block additional calls to Send() if a Send is already in progress.
    /*!
     * \brief WaitForResponse
     * \return
     */
    bool WaitForResponse();             // The loop handles timeouts while waiting

    QString _sendEventMediatorKey;		// Send Event Key
    QString _recieveEventMediatorKey;	// Listen for this result Key

    MediatorCallbackFunc _callback;			// NOT USED - Handled by AsynchMediatorCall

    MediatorArg _sendMediatorArg;			// This is the argument being sent.
    MediatorArg _recieveMediatorArg;        // This is the argument being recieved.
    // Internal mediator callbacks
    MediatorId ResponseRecievedId;
    /*!
     * \brief Elapsed
     * \param startTime
     * \return
     */
    double Elapsed(clock_t startTime);
    bool _willWaitForResponse;          // Turn this on when you want to handle a response event.
    /*!
     * \brief ResponseRecieved
     * \param mediatorArg
     */
    void ResponseRecieved(MediatorArg mediatorArg);	// This internal function handles maintenance when a response is recieved. Then the _callback is called.
    unsigned long _timeoutSecs;			// How long before we stop waiting for a response
};
#endif // ASYNCMEDIATORWORKER_H
