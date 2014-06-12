#ifndef MEDIATIONSESSIONCLASS_H
#define MEDIATIONSESSIONCLASS_H

#include <QDateTime>
#include <QString>
#include "Person.h"

class MediationSessionClass
{
private:
    QDateTime _mediationTime;
    bool _pendingRB, _cancelledRB, _confirmedRB, _rescheduledRB, _fee1Paid, _fee2Paid, _feeFamilyPaid, _feeOtherPaid;
    QString _fee1, _fee2, _feeFamily, _feeOther, _incomeFee1, _incomeFee2, _incomeFeeFamily, _incomeFeeOther;
    Person *_mediator1, *_mediator2, *_observer1, *_observer2;

public:
    MediationSessionClass();

    //getters
    QDateTime getMediationTime() const {return _mediationTime;}
    bool getPendingRB() const {return _pendingRB;}
    bool getCancelledRB() const{return _cancelledRB;}
    bool getConfirmedRB() const{return _confirmedRB;}
    bool getRescheduledRB() const {return _rescheduledRB;}
    bool getFee1Paid() const { return _fee1Paid; }
    bool getFee2Paid() const { return _fee2Paid; }
    bool getFeeFamilyPaid() const { return _feeFamilyPaid; }
    bool getFeeOtherPaid() const { return _feeOtherPaid; }
    QString getFee1() const {return _fee1; }
    QString getFee2() const {return _fee2; }
    QString getFeeOther() const { return _feeOther; }
    QString getFeeFamily() const {return _feeFamily; }
    QString getIncomeFee1() const {return _incomeFee1; }
    QString getIncomeFee2() const { return _incomeFee2; }
    QString getIncomeFeeOther() const {return _incomeFeeOther; }
    QString getIncomeFeeFamily() const { return _incomeFeeFamily; }
    Person *getMediator1() const { return _mediator1; }
    Person *getMediator2() const { return _mediator2; }
    Person *getObserver1() const { return _observer1; }
    Person *getObserver2() const { return _observer2; }

    //setters
    void setMediationTime(QDateTime value) { _mediationTime = value; }
    void setPendingRB(bool value) { _pendingRB = value; }
    void setCancelledRB(bool value) { _cancelledRB = value; }
    void setConfirmedRB(bool value) { _confirmedRB = value; }
    void setRescheduledRB(bool value) { _rescheduledRB = value; }
    void setFee1Paid(bool value) { _fee1Paid = value; }
    void setFee2Paid(bool value) { _fee2Paid = value; }
    void setFeeFamilyPaid(bool value) { _feeFamilyPaid = value; }
    void setFeeOtherPaid(bool value) { _feeOtherPaid = value; }
    void setFee1(QString value) { _fee1 = value; }
    void setFee2(QString value) { _fee2 = value; }
    void setFeeFamily(QString value) { _feeFamily = value; }
    void setFeeOther(QString value) { _feeOther = value; }
    void setIncomeFee1(QString value) { _incomeFee1 = value; }
    void setIncomeFee2(QString value) { _incomeFee2 = value; }
    void setIncomeFeeFamily(QString value) { _incomeFeeFamily = value; }
    void setIncomeFeeOther(QString value)  { _incomeFeeOther = value; }
    void setMediator1(Person *value) { _mediator1 = value; }
    void setMediator2(Person *value) { _mediator2 = value; }
    void setObserver1(Person *value) {_observer1 = value; }
    void setObserver2(Person *value) {_observer2 = value; }

    QString getStatus() const;
    static MediationSessionClass *SampleData();
};

#endif // MEDIATIONSESSIONCLASS_H
