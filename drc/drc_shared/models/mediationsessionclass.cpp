#include "mediationsessionclass.h"
#include <sstream>

MediationSessionClass::MediationSessionClass()
{
    _mediationTime = QDateTime::currentDateTime();
    _pendingRB = true;
    _cancelledRB = _rescheduledRB = _confirmedRB = _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;
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
    srand(_SAMPLE_INDEX);
    int randomNumber = rand() * 100;

    result.setMediationTime(QDateTime::fromTime_t(randomNumber));
    result.setFee1(QString::fromStdString(strId));
    result.setFee2(QString::fromStdString(strId));
    result.setFeeFamily(QString::fromStdString(strId));
    result.setFeeOther(QString::fromStdString(strId));

    result.setMediator1(Person::SampleData());
    result.setMediator2(Person::SampleData());
    result.setObserver1(Person::SampleData());
    return result;
}
