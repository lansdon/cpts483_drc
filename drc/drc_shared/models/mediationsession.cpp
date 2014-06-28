#include "mediationsession.h"
#include <sstream>
#include <QDateTime>
#include <QDebug>
#include "DRCModels.h"

MediationSession::MediationSession()
    : _supportCount(0)
{
    _state = SessionStates::SESSION_STATE_PENDING;
    _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;

}


QString MediationSession::Parse()
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += QString::number(this->GetState());
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
    toReturn += single_quote + this->getMediator1() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getMediator2() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getObserver1() + single_quote;
    toReturn += ", ";
    toReturn += single_quote + this->getObserver2() + single_quote;

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
    result->setMediator1(QString::fromStdString("Mediator" + strId));
    result->setMediator2(QString::fromStdString("Mediator" + strId));
    result->setObserver1(QString::fromStdString("Observer " + strId));
    result->setObserver2(QString::fromStdString("Observer " + strId));
    result->setSupportCount(qrand()%10);

    return result;
}

//QDataStream& MediationSession::operator <<(QDataStream &out, MediationSession &MS)
//{
//    out << MS.getMediationTime();
//    out << MS.getMediationCreation();
//    out << MS.GetState();
//    out << MS.getFee1Paid();
//    out << MS.getFee2Paid();
//    out << MS.getFeeFamilyPaid();
//    out << MS.getFeeOtherPaid();
//    out << MS.getFee1();
//    out << MS.getFee2();
//    out << MS.getFeeFamily();
//    out << MS.getFeeOther();
//    out << MS.getIncomeFee1();
//    out << MS.getIncomeFee2();
//    out << MS.getIncomeFeeFamily();
//    out << MS.getIncomeFeeOther();
//    out << *MS.getMediator1();
//    out << *MS.getMediator2();
//    out << *MS.getObserver1();
//    out << *MS.getObserver2();

//    return out;
//}

//QDataStream& MediationSession::operator >>(QDataStream &in, MediationSession &MS)
//{
//    QDateTime a, b;
//    SessionStates c;
//    bool d, e, f, g;
//    QString h, i, j, k, l, m, n, o;
//    Person p, q, r, s;

//    in>>a;
//    in>>b;
//    in>>c;
//    in>>d;
//    in>>e;
//    in>>f;
//    in>>g;
//    in>>h;
//    in>>i;
//    in>>j;
//    in>>k;
//    in>>l;
//    in>>m;
//    in>>n;
//    in>>o;
//    in>>p;
//    in>>q;
//    in>>r;
//    in>>s;

//    MS.setMediationTime(a);
//    MS.setMediationCreation(b);
//    MS.SetState(c);
//    MS.setFee1Paid(d);
//    MS.setFee2Paid(e);
//    MS.setFeeFamilyPaid(f);
//    MS.setFeeOtherPaid(g);
//    MS.setFee1(h);
//    MS.setFee2(i);
//    MS.setFeeFamily(j);
//    MS.setFeeOther(k);
//    MS.setIncomeFee1(l);
//    MS.setIncomeFee2(m);
//    MS.setIncomeFeeFamily(n);
//    MS.setIncomeFeeOther(o);
//    MS.setMediator1(new Person(p));
//    MS.setMediator2(new Person(q));
//    MS.setObserver1(new Person(r));
//    MS.setObserver2(new Person(s));

//    return in;
//}
