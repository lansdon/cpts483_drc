#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QDateTime>
#include <QString>
#include "drctypes.h"
#include "DBBaseObject.h"
#include "clientsessiondata.h"
#include <QTextCursor>

/*!
 * \brief The MediationSession class
 */
class MediationSession : public DBBaseObject
{
private:
    QDateTime _mediationTime;
    SessionStates _state;
    QString _mediator1, _mediator2, _observer1, _observer2;
    ClientSessionDataVector _clientSessionDataVector;
    bool _isShuttle;
    SessionOutcomes _outcome;

public:
    /*!
     * \brief MediationSession
     */
    MediationSession();
    /*!
     * \brief MediationSession
     * \param numOfClients
     */
    MediationSession(uint numOfClients);

    //Virtual overrides
    /*!
     * \brief Parse
     * \return
     */
    QString Parse();
    /*!
     * \brief UpdateParse
     * \return
     */
    QString UpdateParse();
    /*!
     * \brief table
     * \return
     */
    QString table();
    /*!
     * \brief DuplicateQuery
     * \return
     */
    QString DuplicateQuery();
    /*!
     * \brief SearchQuery
     * \return
     */
    QString SearchQuery();
    /*!
     * \brief GetIdRowName
     * \return
     */
    QString GetIdRowName();

    //getters
    /*!
     * \brief getMediationTime
     * \return
     */
    QDateTime getMediationTime() const {return _mediationTime;}
    /*!
     * \brief getMediator1
     * \return
     */
    QString getMediator1() const { return _mediator1; }
    /*!
     * \brief getMediator2
     * \return
     */
    QString getMediator2() const { return _mediator2; }
    /*!
     * \brief getObserver1
     * \return
     */
    QString getObserver1() const { return _observer1; }
    /*!
     * \brief getObserver2
     * \return
     */
    QString getObserver2() const { return _observer2; }
    /*!
     * \brief GetState
     * \return
     */
    SessionStates GetState() { return _state; }
    /*!
     * \brief getClientSessionDataVector
     * \return
     */
    ClientSessionDataVector *getClientSessionDataVector() { return &_clientSessionDataVector; }
    /*!
     * \brief getClientSessionDataVectorAt
     * \param index
     * \return
     */
    ClientSessionData *getClientSessionDataVectorAt(int index) {return _clientSessionDataVector.at(index); }
    /*!
     * \brief getScheduledDate
     * \return
     */
    QDate getScheduledDate() const { return _mediationTime.date(); }
    /*!
     * \brief getScheduledTime
     * \return
     */
    QTime getScheduledTime() const { return _mediationTime.time(); }
    /*!
     * \brief getOutcome
     * \return
     */
    SessionOutcomes getOutcome() { return _outcome; }
    bool GetIsShuttle() { return _isShuttle; }


    //setters
    /*!
     * \brief setMediationTime
     * \param value
     */
    void setMediationTime(QDateTime value) { _mediationTime = value; }
    /*!
     * \brief setMediator1
     * \param value
     */
    void setMediator1(QString value) { _mediator1 = value; }
    /*!
     * \brief setMediator2
     * \param value
     */
    void setMediator2(QString value) { _mediator2 = value; }
    /*!
     * \brief setObserver1
     * \param value
     */
    void setObserver1(QString value) {_observer1 = value; }
    /*!
     * \brief setObserver2
     * \param value
     */
    void setObserver2(QString value) {_observer2 = value; }
    /*!
     * \brief SetState
     * \param state
     */
    void SetState(SessionStates state) { _state = state; }
    /*!
     * \brief setClientSessionDataVector
     * \param value
     */
    void setClientSessionDataVector(ClientSessionDataVector value) { _clientSessionDataVector = value; }
    /*!
     * \brief setScheduledDate
     * \param value
     */
    void setScheduledDate(QDate value) { _mediationTime.setDate(value); }
    /*!
     * \brief setScheduledTime
     * \param value
     */
    void setScheduledTime(QTime value) { _mediationTime.setTime(value); }
    /*!
     * \brief setOutcome
     * \param value
     */
    void setOutcome(SessionOutcomes value) { _outcome = value; }
    void SetIsShuttle(bool isShuttle) { _isShuttle = isShuttle; }


    /*!
     * \brief getStatus
     * \return
     */
    QString getStatus() const;
    /*!
     * \brief getFeeStatus
     * \return
     */
    QString getFeeStatus() const;
    /*!
     * \brief isFullyPaid
     * \return
     */
    bool isFullyPaid() const;
    /*!
     * \brief SampleData
     * \return
     */
    static MediationSession *SampleData();
    /*!
     * \brief addClientSessionData
     * \param value
     */
    void addClientSessionData(ClientSessionData *value) { _clientSessionDataVector.push_back(value); }
    /*!
     * \brief removeClientSessionData
     * \param value
     */
    void removeClientSessionData(uint value);
    /*!
     * \brief BuildToPDF
     * \param cursor
     */
    void BuildToPDF(QTextCursor& cursor);
};

#endif // MEDIATIONSESSION_H
