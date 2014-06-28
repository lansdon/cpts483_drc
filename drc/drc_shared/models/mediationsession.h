#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QDateTime>
#include <QString>
#include "drctypes.h"
#include "DBBaseObject.h"

class MediationSession : public DBBaseObject
{
private:
    QDateTime _mediationTime, _mediationCreation;
    SessionStates _state;
    bool _fee1Paid, _fee2Paid, _feeFamilyPaid, _feeOtherPaid;
    QString _fee1, _fee2, _feeFamily, _feeOther, _incomeFee1, _incomeFee2, _incomeFeeFamily, _incomeFeeOther;
    QString _mediator1, _mediator2, _observer1, _observer2;
    int _supportCount;  // total number of support people
public:
    MediationSession();

    //Virtual overrides
    QString Parse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    //getters
    QDateTime getMediationTime() const {return _mediationTime;}
    QDateTime getMediationCreation() const { return _mediationCreation; }
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
    QString getMediator1() const { return _mediator1; }
    QString getMediator2() const { return _mediator2; }
    QString getObserver1() const { return _observer1; }
    QString getObserver2() const { return _observer2; }
    SessionStates GetState() { return _state; }
    int GetSupportCount() { return _supportCount; }

    //setters
    void setSupportCount(int count) { _supportCount = count; }
    void setMediationTime(QDateTime value) { _mediationTime = value; }
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
    void setMediator1(QString value) { _mediator1 = value; }
    void setMediator2(QString value) { _mediator2 = value; }
    void setObserver1(QString value) {_observer1 = value; }
    void setObserver2(QString value) {_observer2 = value; }
    void SetState(SessionStates state) { _state = state; }
    void setMediationCreate(QDateTime value) { _mediationCreation = value; }

    QString getStatus() const;
    QString getFeeStatus() const;
    static MediationSession *SampleData();


};

#endif // MEDIATIONSESSION_H
