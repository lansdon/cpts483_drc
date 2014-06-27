#include "mediationsession.h"
#include <sstream>
#include <QDateTime>
#include <QDebug>
#include "DRCModels.h"

MediationSession::MediationSession()
{
    _mediationCreation = QDateTime::currentDateTime();
    _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;
    _mediator1 = new Person();
    _mediator2 = new Person();
    _observer1 = new Person();
    _observer2 = new Person();

}


QString MediationSession::Parse()
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += this->GetState();
    toReturn += ", ";

    // Paid amounts
    if(this->getFee1Paid())
        toReturn += "1";
    else
        toReturn += "0";
    toReturn += ", ";
    if(this->getFee2Paid())
        toReturn += "1";
    else
        toReturn += "0";
    toReturn += ", ";
    if(this->getFeeFamilyPaid())
        toReturn += "1";
    else
        toReturn += "0";
    toReturn += ", ";
    if(this->getFeeOtherPaid())
        toReturn += "1";
    else
        toReturn += "0";
    toReturn += ", ";

    // Due amounts
    toReturn += this->getFee1();
    toReturn += ", ";
    toReturn += this->getFee2();
    toReturn += ", ";
    toReturn += this->getFeeFamily();
    toReturn += ", ";
    toReturn += this->getFeeOther();
    toReturn += ", ";

    // Income Fee amounts
    toReturn += this->getIncomeFee1();
    toReturn += ", ";
    toReturn += this->getIncomeFee2();
    toReturn += ", ";
    toReturn += this->getIncomeFeeFamily();
    toReturn += ", ";
    toReturn += this->getIncomeFeeOther();
    toReturn += ", ";

    // Mediator Info
    toReturn += single_quote + this->getMediator1()->FullName() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getMediator2()->FullName() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getObserver1()->FullName() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getObserver2()->FullName() + single_quote;

    //toReturn = "Hello World";

    return toReturn;
}

QString MediationSession::table()
{
    return QString("Session_Table");
}

QString MediationSession::DuplicateQuery()
{

}

QString MediationSession::SearchQuery()
{

}


QString MediationSession::getStatus() const
{
    return StringForSessionStates(_state);
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
    partial1 = partial2 = partial3 = partial4 = false;
    paidInFull = true;

    //check if there is any partial payments
    if(!_fee1.isEmpty() && _fee1Paid)
        partial1 = true;
    if(!_fee2.isEmpty() && _fee2Paid)
        partial2 = true;
    if(!_feeFamily.isEmpty() && _feeFamilyPaid)
        partial3 = true;
    if(!_feeOther.isEmpty() && _feeOtherPaid)
        partial4 = true;

    //check if paid in full
    if((!_fee1.isEmpty() && !partial1) || (!_fee2.isEmpty() && !partial2) || (!_feeFamily.isEmpty() && !partial3) || (!_feeOther.isEmpty() && !partial4))
        paidInFull = false;


    if(_fee1.isEmpty() && _fee2.isEmpty() && _feeFamily.isEmpty() && _feeOther.isEmpty())           //check if all fees are empty
        return "No fees added";
    else if(paidInFull)                                                                             //check if paid in full
        return "Paid In Full";
    else if(partial1 || partial2 || partial3 || partial4)                                           //check if there are any partial payments
        return "Partial Payment";
    else                                                                                            //else it's not paid
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
    result->SetState((SessionStates)(qrand() % 5));
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
