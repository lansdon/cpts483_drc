#ifndef MEDIATIONPROCESS_H
#define MEDIATIONPROCESS_H

#include <vector>
#include "drctypes.h"
#include <QDate>
#include "party.h"

class Person;

class MediationProcess
{
public:
    MediationProcess();

    static MediationProcess* SampleData();

    // Accessors
    Party* GetParty1() { return &_party1; }
    Party* GetParty2() { return &_party2; }
    DisputeTypes GetDisputeType() { return _disputeType; }
    CountyIds GetCountyId() { return _countyOfMediation; }
    std::vector<QString>& GetNotes() { return _mediationNotes; }
    ReferralTypes GetReferralType() { return _referalSource; }
    QDate GetCreationDate() { return _creationDate; }
    DisputeProcessStates GetCurrentState() { return _processState; }
    bool GetRequiresSpanish() { return _requiresSpanish; }

    void SetParty1(Party* party) { _party1 = *party; }
    void SetParty2(Party* party) { _party2 = *party; }
    void SetDisputeType(DisputeTypes type) { _disputeType = type; }
    void SetCountyId(CountyIds countyId) { _countyOfMediation = countyId; }
    void AddNote(QString note) { _mediationNotes.push_back(note); }
    void SetReferralType(ReferralTypes type) { _referalSource = type; }
    void SetCreationDate(QDate date) { _creationDate = date; }
    void SetProcessState(DisputeProcessStates state) { _processState = state; }
    void SetRequiresSpanish(bool requiresSpanish) { _requiresSpanish = requiresSpanish; }

    // Helpers
    int GetAffectedChildrenCount() { return _party1.GetAffectedChildren() + _party2.GetAffectedChildren(); }
private:

    Party _party1;

    Party _party2;

    DisputeTypes _disputeType;

    QDate _creationDate;

    DisputeProcessStates _processState;

    CountyIds _countyOfMediation;

    std::vector<QString> _mediationNotes;

    ReferralTypes _referalSource;

    bool _requiresSpanish;

};

#endif // MEDIATIONPROCESS_H
