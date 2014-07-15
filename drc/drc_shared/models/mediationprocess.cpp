#include "mediationprocess.h"

#include <sstream>
#include "DRCModels.h"
#include "drctypes.h"
#include <random>
#include "DBBaseObject.h"

//Values going into MediationProcess Table
//id
//disputeType
//creationDate
//updatedDate
//processState
//countyOfMediation
//mediationNotes
//referalSource
//requiresSpanish
//sessionType

//Objects to extract from MediationProcess
//Parties
//Mediation Sessions

//Objects to extract from Parties
//Person

MediationProcess::MediationProcess()
    : DBBaseObject()
    , _stateTransition(0)
    , _activeStateTransition(0)
    , _disputeType(DISPUTE_T_NONE)
    , _processState(PROCESS_STATE_NONE)
    , _countyOfMediation(COUNTY_NONE)
    , _referalSource(REFERRAL_T_NONE)
    , _requiresSpanish(false)
    , _isCourtCase(false)
    , _courtCaseType(COURT_T_NONE)
    , _courtOrderType(COURT_ORDER_T_NONE)
    , _infoOnly(false)
    , _sessionType(MEDIATION_SESSION)
{

}


MediationProcess::~MediationProcess()
{
}

QString MediationProcess::Parse()
{
    // UPDATED 7-14-14 for new schema
    QString toReturn = QString("%1, '%2', '%3', '%4', '%5', %6, %7, %8")
            .arg(QString::number(this->GetDisputeType()))
            .arg(this->GetCreatedDate().toString("yyyy-MM-dd"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd"))
            .arg(this->GetCreatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(QString::number(this->GetState()))
            .arg(QString::number(this->GetInternalState()))
            .arg(QString::number(this->GetCountyId()));

    toReturn += QString("%1, '%2', '%3', '%4', '%5', %6, '%7', '%8', '%9', '%10', %11")
            .arg(QString::number(this->GetReferralType()))
            .arg(QString::number(this->GetInquiryType()))
            .arg(this->GetInfoOnly())
            .arg(this->GetIsCourtCase())
            .arg(this->GetCourtDate().toString("yyyy-MM-dd"))
            .arg(QString::number(this->GetCourtType()))
            .arg(QString::number(this->GetCourtOrderType()))
            .arg(this->GetCourtOrderExpiration().toString("yyyy-MM-dd"))
            .arg(this->GetIsShuttle())
            .arg(QString::number(this->GetRequiresSpanish())
            .arg(QString::number(this->GetSessionType())));

    return toReturn;
}

QString MediationProcess::UpdateParse()
{
    //Updated 7-14-14 for new schema
    QString toUpdate = QString("DisputeType = %1, UpdatedDate = '%2', UpdatedDateTime = '%3', DisputeState = %4, DisputeInternalState = %5, DisputeCounty = %6")
            .arg(QString::number(this->GetDisputeType()))
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"))
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(QString::number(this->GetState()))
            .arg(QString::number(this->GetInternalState()))
            .arg(QString::number(this->GetCountyId()));

    toUpdate += QString("ReferalSource = '%1', TranslatorRequired = '%2', InquiryType = %3, InfoOnly = '%4', CourtCase = '%5', ")
            .arg(QString::number(this->GetReferralType()))
            .arg(QString::number(this->GetRequiresSpanish()))
            .arg(QString::number(this->GetInquiryType()))
            .arg(this->GetInfoOnly())
            .arg(this->GetIsCourtCase());

    toUpdate += QString("CourtDate = '%1', CourtCaseType = %2, CourtOrderType = %3, CourtOrderExpiration = '%4', ShuttleRequired = '%5', TranslatorRequired = '%6', SessionType = %7")
            .arg(this->GetCourtDate().toString("yyyy-MM-dd"))
            .arg(QString::number(this->GetCourtType()))
            .arg(QString::number(this->GetCourtOrderType()))
            .arg(this->GetCourtOrderExpiration().toString("yyyy-MM-dd"))
            .arg(this->GetIsShuttle())
            .arg(this->GetRequiresSpanish())
            .arg(QString::number(this->GetSessionType()));

    return toUpdate;
}

QString MediationProcess::GetIdRowName()
{
    return "process_id";
}

QString MediationProcess::table()
{
    return QString("Mediation_Table");
}
void MediationProcess::addMediation()
{
    //_parties.size()
    _mediationSessionVector.push_back(new MediationSession());
}

void MediationProcess::removeParty(int value)
{
    if(_parties.size() > 0)
        _parties.erase(_parties.begin()+ (value));

    for(int i = 0; i < (int)_mediationSessionVector.size(); i++)
    {
        MediationSession *temp = _mediationSessionVector.at(i);
        temp->removeClientSessionData(value);
    }
}

// Test Data - Fill the object with test values in every field.
MediationProcess *MediationProcess::SampleData()
{
    MediationProcess *result = new MediationProcess();

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();
    result->GetParties()->clear();
    for(int i=0; i < rand() % 4 + 1; ++i)
        result->AddParty(Party::SampleData());

    result->_countyOfMediation = (CountyIds)(rand() % 3 + 1);
    result->_disputeType = (DisputeTypes)(rand() % 7 + 1);
    result->_requiresSpanish = rand() % 2;
    result->_processInternalState = (DisputeProcessInternalStates)( rand() % 5 + 1 );
    result->_referalSource = (ReferralTypes)(rand() % 8 + 1);
    result->_sessionType = (SessionTypes) (rand() % 3 + 1);

    MediationSessionVector *temp = new MediationSessionVector;
    for(int i = 0; i< rand() % 5 + 1; i++)
        temp->push_back(MediationSession::SampleData());
    result->setMediationSessionVector(temp);
    for(int i=0; i < 5; ++i)
        result->GetNotes()->push_back(new Note("Some more mediation notes " + QString::number(i)));

    return result;
}

int MediationProcess::GetAffectedChildrenCount()
{
    int total = 0;
    foreach(auto p, _parties)
        total += p->GetAffectedChildren();
    return total;
}

void MediationProcess::updateClientSessions(int value)
{
    for(int i = 0; i < (int)_mediationSessionVector.size(); i++)
    {
        ClientSessionDataVector *a  = _mediationSessionVector.at(i)->getClientSessionDataVector();
        if((int)a->size() != value)
        {
            for(int j = (int)a->size(); j < value; j++)
            {
                a->push_back(new ClientSessionData());
            }
        }
    }
}

// Report Helpers
// Returns true if the mediation process has at least one session that has resulted in an agreement
// a solved problem or been self resolved.
bool MediationProcess::IsSettled()
{
    foreach(MediationSession* session, _mediationSessionVector)
        if(session->getOutcome() == SESSION_OUTCOME_AGREEMENT || session->getOutcome() == SESSION_OUTCOME_PROBLEM_SOLVING || session->getOutcome() == SESSION_OUTCOME_SELF_RESOLVED)
            return true;

    return false;
}

void MediationProcess::AddParty(Party *party)
{
     _parties.push_back(party);
     for(int i = 0; i < (int)_mediationSessionVector.size(); i++)
     {
         MediationSession *temp = _mediationSessionVector.at(i);
         temp->addClientSessionData(new ClientSessionData());
     }
}
