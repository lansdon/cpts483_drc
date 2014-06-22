#include "mediationprocess.h"

#include <sstream>
#include "DRCModels.h"
#include "drctypes.h"
#include <random>

MediationProcess::MediationProcess()
{
    _mediationSessionClassVector = new MediationSessionClassVector();
    //_parties = new PartyVector();
    _parties.push_back(new Party());
    _parties.push_back(new Party());
    _creationDate = QDateTime::currentDateTime();
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
    result->GetParties().clear();
    for(int i=0; i < rand() % 4 + 1; ++i)
        result->AddParty(Party::SampleData());

    result->_countyOfMediation = (CountyIds)(rand() % 4 + 1);
    result->_disputeType = (DisputeTypes)(rand() % 7 + 1);
    result->_requiresSpanish = rand() % 2;
    result->_processState = (DisputeProcessStates)( rand() % 5 + 1 );
    result->_referalSource = (ReferralTypes)(rand() % 8 + 1);
    result->SetCreationDate(QDateTime::currentDateTime());
    MediationSessionClassVector *temp = new MediationSessionClassVector;
    for(int i = 0; i< rand() % 5 + 1; i++)
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


