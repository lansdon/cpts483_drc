#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QDateTime>
#include <QString>
#include "drctypes.h"
#include "DBBaseObject.h"
#include "clientsessiondata.h"
#include <QTextCursor>

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
    MediationSession();
    MediationSession(uint numOfClients);
    //Virtual overrides
    QString Parse();
    QString ColumnNames();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    QString GetIdRowName();

    //getters
    QDateTime getMediationTime() const {return _mediationTime;}

    QString getMediator1() const { return _mediator1; }
    QString getMediator2() const { return _mediator2; }
    QString getObserver1() const { return _observer1; }
    QString getObserver2() const { return _observer2; }
    SessionStates GetState() { return _state; }
    ClientSessionDataVector *getClientSessionDataVector() { return &_clientSessionDataVector; }
    ClientSessionData *getClientSessionDataVectorAt(int index) {return _clientSessionDataVector.at(index); }
    QDate getScheduledDate() const { return _mediationTime.date(); }
    QTime getScheduledTime() const { return _mediationTime.time(); }
    SessionOutcomes getOutcome() { return _outcome; }
    bool GetIsShuttle() { return _isShuttle; }


    //setters
    void setMediationTime(QDateTime value) { _mediationTime = value; }
    void setMediator1(QString value) { _mediator1 = value; }
    void setMediator2(QString value) { _mediator2 = value; }
    void setObserver1(QString value) {_observer1 = value; }
    void setObserver2(QString value) {_observer2 = value; }
    void SetState(SessionStates state) { _state = state; }
    void setClientSessionDataVector(ClientSessionDataVector value) { _clientSessionDataVector = value; }
    void setScheduledDate(QDate value) { _mediationTime.setDate(value); }
    void setScheduledTime(QTime value) { _mediationTime.setTime(value); }
    void setOutcome(SessionOutcomes value) { _outcome = value; }
    void SetIsShuttle(bool isShuttle) { _isShuttle = isShuttle; }


    QString getStatus() const;
    QString getFeeStatus() const;
    bool isFullyPaid() const;
    static MediationSession *SampleData();
    void addClientSessionData(ClientSessionData *value) { _clientSessionDataVector.push_back(value); }
    void removeClientSessionData(uint value);

    void BuildToPDF(QTextCursor& cursor);

};

#endif // MEDIATIONSESSION_H
