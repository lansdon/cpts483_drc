#include "mediationprocess.h"

#include <sstream>
#include "DRCModels.h"
#include "drctypes.h"


MediationProcess::MediationProcess()
{
    _mediationSessionClassVector = new MediationSessionClassVector();
//    _party1 = new Party();
//    _party2 = new Party();
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

//proably needs to be removed
//    result->_party1 = Party::SampleData();
//    result->_party2 = Party::SampleData();

    result->AddParty(Party::SampleData());
    result->AddParty(Party::SampleData());

    result->_countyOfMediation = COUNTY_BENTON;
    result->_disputeType = DISPUTE_T_NEIGHBORHOOD;
    result->_requiresSpanish = true;
    result->_processState = PROCESS_STATE_INITIATED;
    result->_referalSource = REFERRAL_T_INTERNET;
    result->SetCreationDate(QDateTime::currentDateTime());
    MediationSessionClassVector *temp = new MediationSessionClassVector;
    for(int i = 0; i< 3; i++)
        temp->push_back(MediationSessionClass::SampleData());
    result->setMediationSessionClassVector(temp);
    for(int i=0; i < 25; ++i)
        result->GetNotes().push_back("Some more mediation notes " + QString::number(i));



    return result;
}

int MediationProcess::GetAffectedChildrenCount()
{
    int total = 0;
    foreach(auto p, _parties)
        total += p->GetAffectedChildren();
    return total;
}
