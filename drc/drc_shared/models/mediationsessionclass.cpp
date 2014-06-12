#include "mediationsessionclass.h"
#include <sstream>
#include <QDateTime>

MediationSessionClass::MediationSessionClass()
{
    _mediationTime = QDateTime::currentDateTime();
    _pendingRB = true;
    _cancelledRB = _rescheduledRB = _confirmedRB = _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;
    _mediator1 = new Person();
    _mediator2 = new Person();
    _observer1 = new Person();
    _observer2 = new Person();
}

QString MediationSessionClass::getStatus() const
{
    return _pendingRB ? "Pending" : _cancelledRB ? "Cancelled" : _rescheduledRB ? "Reschecduled" : _confirmedRB ? "Confirmed" : "Error In Reading Status";
}

MediationSessionClass MediationSessionClass::SampleData()
{

    MediationSessionClass result;

     // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();
    qint64 a;
    QDateTime::fromMSecsSinceEpoch(a);
    srand( a/1000);
    int randomNumber = rand() * 100000;
    int randomStatus = rand() % 4;
    result.setPendingRB(false);
    switch(randomStatus)
    {
    case 0:
        result.setPendingRB(true);
        break;
    case 1:
        result.setConfirmedRB(true);
        break;
    case 2:
        result.setCancelledRB(true);
        break;
    case 3:
        result.setRescheduledRB(true);
    }

    result.setMediationTime(QDateTime::fromTime_t(randomNumber));
    result.setFee1(QString::fromStdString(strId));
    result.setFee2(QString::fromStdString(strId));
    result.setFeeFamily(QString::fromStdString(strId));
    result.setFeeOther(QString::fromStdString(strId));
    result.setFee1Paid(true);
    result.setFee2Paid(true);
    result.setIncomeFee1(QString::fromStdString(strId));
    result.setIncomeFee2(QString::fromStdString(strId));
    result.setIncomeFeeFamily(QString::fromStdString(strId));
    result.setIncomeFeeOther(QString::fromStdString(strId));
    result.setMediator1(Person::SampleData());
    result.setMediator2(Person::SampleData());
    result.setObserver1(Person::SampleData());
    result.setObserver2(Person::SampleData());

    return result;
}
