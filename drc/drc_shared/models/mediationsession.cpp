#include "mediationsession.h"
#include <sstream>
#include <QDateTime>
#include <QDebug>
#include "DRCModels.h"

MediationSession::MediationSession()
{
    _mediationTime = QDateTime::currentDateTime();
    _pendingRB = true;
    _cancelledRB = _rescheduledRB = _confirmedRB = _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;
    _mediator1 = new Person();
    _mediator2 = new Person();
    _observer1 = new Person();
    _observer2 = new Person();

}

QString MediationSession::getStatus() const
{
    return _pendingRB ? "Pending" : _cancelledRB ? "Cancelled" : _rescheduledRB ? "Reschecduled" : _confirmedRB ? "Confirmed" : "Error In Reading Status";
}

QString MediationSession::getFeeStatus() const
{
//    if(!_fee1.isEmpty() && !_fee2.isEmpty() && !_feeFamily.isEmpty() && !_feeOther.isEmpty())
//    {
//        if(_fee1Paid && _fee2Paid && _feeFamilyPaid && _feeOtherPaid)
//            return "Paid";
//        else
//            return "Partial";
//    }
//    else if(!_fee1.isEmpty() && !_fee2.isEmpty() && !_feeFamily.isEmpty())
    bool partial1, partial2, partial3, partial4, paidInFull;
    partial1 = partial2 = partial3 = partial4 = paidInFull = true;
    if(!_fee1.isEmpty() && !_fee1Paid)
        partial1 = false;
    if(!_fee2.isEmpty() && !_fee2Paid)
        partial2 = false;
    if(!_feeFamily.isEmpty() && !_feeFamilyPaid)
        partial3 = false;
    if(!_feeOther.isEmpty() && !_feeOtherPaid)
        partial4 = false;
    if(!partial1 || !partial2 || !partial3 || !partial4)
        paidInFull = false;
    if(paidInFull && (!_fee1Paid || !_fee2Paid || !_feeFamilyPaid || !_feeOtherPaid))
        return "No fees added";
    else if(paidInFull)
        return "Paid In Full";
    else if(partial1 || partial2 || partial3 || partial4)
        return "Partial Payment";
    else
        return "Not Paid";
}

MediationSession *MediationSession::SampleData()
{

    MediationSession *result = new MediationSession();

     // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();

    int randomNumber = qrand() * 100000;
    int randomStatus = qrand() % 4;
    result->setPendingRB(false);
    switch(randomStatus)
    {
    case 0:
        result->setPendingRB(true);
        break;
    case 1:
        result->setConfirmedRB(true);
        break;
    case 2:
        result->setCancelledRB(true);
        break;
    case 3:
        result->setRescheduledRB(true);
    }

    result->setMediationTime(QDateTime::fromTime_t(randomNumber));
    result->setFee1(QString::fromStdString(strId));
    result->setFee2(QString::fromStdString(strId));
    result->setFeeFamily(QString::fromStdString(strId));
    result->setFeeOther(QString::fromStdString(strId));
    result->setFee1Paid(true);
    result->setFee2Paid(true);
    result->setIncomeFee1(QString::fromStdString(strId));
    result->setIncomeFee2(QString::fromStdString(strId));
    result->setIncomeFeeFamily(QString::fromStdString(strId));
    result->setIncomeFeeOther(QString::fromStdString(strId));
    result->setMediator1(Person::SampleData());
    result->setMediator2(Person::SampleData());
    result->setObserver1(Person::SampleData());
    result->setObserver2(Person::SampleData());

    return result;
}
