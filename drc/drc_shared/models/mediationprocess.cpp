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

//Objects to extract from MediationProcess
//Parties
//Mediation Sessions

//Objects to extract from Parties
//Person

MediationProcess::MediationProcess() : DBBaseObject()
{
    _creationDate = QDateTime::currentDateTime();
//    AddParty(new Party());
}
MediationProcess::MediationProcess(PartyVector parties, uint stateTrans, uint actStateTrans, DisputeTypes disputeType,
                                   QDateTime creationDate, DisputeProcessStates processState, CountyIds county,
                                   MediationNotesVector mediationNotes, ReferralTypes reftype, bool spanish, MediationSessionVector sessions) :
    _parties(parties), _stateTransition(stateTrans), _activeStateTransition(actStateTrans), _disputeType(disputeType),
    _creationDate(creationDate), _processState(processState), _countyOfMediation(county), _mediationNotes(mediationNotes),
    _referalSource(reftype), _requiresSpanish(spanish), _mediationSessionVector(sessions){}


MediationProcess::~MediationProcess()
{
}

QString MediationProcess::Parse()
{
    QString toReturn = QString("%1, '%2', '%3', %4, %5, ")
            .arg(QString::number(this->GetDisputeType()))
            .arg(this->GetCreationDate().toString("yyyy-MM-dd"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd"))
            .arg(QString::number(this->GetCurrentState()))
            .arg(QString::number(this->GetCountyId()));

    std::vector<QString> Notebook;// = this->GetNotes();

    Notebook.push_back("Hello World");
    QString NotebookInOneLine = "";

    //Sloppy as hell.  Forgive me.
    foreach (QString line, Notebook)
    {
        NotebookInOneLine += line + "\n";
    }

    toReturn += QString("'%1', '%2', '%3'")
            .arg(NotebookInOneLine)
            .arg(QString::number(this->GetReferralType()))
            .arg(QString::number(this->GetRequiresSpanish()));

    return toReturn;
}

QString MediationProcess::table()
{
    return QString("Mediation_Table");
}
void MediationProcess::addMediation()
{
    _mediationSessionVector.push_back(new MediationSession());
}

void MediationProcess::removeParty(int value)
{
    if(_parties.size() > 0)
        _parties.erase(_parties.begin()+ (value));
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
    result->_processState = (DisputeProcessStates)( rand() % 5 + 1 );
    result->_referalSource = (ReferralTypes)(rand() % 8 + 1);
    result->SetCreationDate(QDateTime::currentDateTime());
    MediationSessionVector *temp = new MediationSessionVector;
    for(int i = 0; i< rand() % 5 + 1; i++)
        temp->push_back(MediationSession::SampleData());
    result->setMediationSessionVector(temp);
    for(int i=0; i < 25; ++i)
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


