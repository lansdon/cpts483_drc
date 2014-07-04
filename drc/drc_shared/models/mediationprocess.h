#ifndef MEDIATIONPROCESS_H
#define MEDIATIONPROCESS_H

#include <vector>
#include "drctypes.h"
#include <QDate>
#include "DBBaseObject.h"
#include "party.h"
#include "Note.h"


class MediationProcess : public DBBaseObject
{
public:
    MediationProcess();
    MediationProcess(PartyVector parties, uint stateTrans, uint actStateTrans,
                     DisputeTypes disputeType, QDateTime creationDate, DisputeProcessStates processState, DisputeProcessInternalStates processInternalState,
                     CountyIds county, MediationNotesVector mediationNotes, ReferralTypes reftype, bool spanish, MediationSessionVector sessions);
    virtual ~MediationProcess();

    // Required Overrides
    QString Parse();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    QString GetIdRowName();

    static MediationProcess* SampleData();

    // Accessors
    PartyVector* GetParties() { return &_parties; }
    Party* GetPartyAtIndex(unsigned int index) { return _parties.size() > index ? _parties[index] : nullptr; }
    void AddParty(Party* party) { _parties.push_back(party); }

    DisputeTypes GetDisputeType() { return _disputeType; }
    CountyIds GetCountyId() { return _countyOfMediation; }
    MediationNotesVector* GetNotes() { return &_mediationNotes; }
    ReferralTypes GetReferralType() { return _referalSource; }

    DisputeProcessStates GetState() { return _processState; }
    DisputeProcessInternalStates GetInternalState() { return _processInternalState; }
    bool GetRequiresSpanish() { return _requiresSpanish; }
    MediationSessionVector *getMediationSessionVector() {return &_mediationSessionVector;}


    void SetDisputeType(DisputeTypes type) { _disputeType = type; }
    void SetCountyId(CountyIds countyId) { _countyOfMediation = countyId; }
    void AddNote(QString note) { _mediationNotes.push_back(new Note(note)); }
    void SetReferralType(ReferralTypes type) { _referalSource = type; }

    void SetState(DisputeProcessStates state) { _processState = state; }
    void SetInternalState(DisputeProcessInternalStates state) { _processInternalState = state; }
    void SetRequiresSpanish(bool requiresSpanish) { _requiresSpanish = requiresSpanish; }
    uint getStateTransition() {return _stateTransition;}
    void setStateTransition(uint input) {_stateTransition = input;}
    void setMediationSessionVector(MediationSessionVector *value) {if(value) _mediationSessionVector = *value;}
    uint getActiveStateTransition() { return _activeStateTransition; }
    void setActiveStateTransition(uint value) {_activeStateTransition = value; }

    // Helpers
    int GetAffectedChildrenCount();
    void addMediation();
    void removeParty(int value);

private:

    PartyVector _parties;

    uint _stateTransition;
    uint _activeStateTransition;

    DisputeTypes _disputeType;

    DisputeProcessInternalStates _processInternalState;
    DisputeProcessStates _processState;

    CountyIds _countyOfMediation;

    MediationNotesVector _mediationNotes;

    ReferralTypes _referalSource;

    bool _requiresSpanish;

    MediationSessionVector _mediationSessionVector;


};

#endif // MEDIATIONPROCESS_H
