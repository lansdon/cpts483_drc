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
    void AddParty(Party* party);

    DisputeTypes GetDisputeType() { return _disputeType; }
    CountyIds GetCountyId() { return _countyOfMediation; }
    MediationNotesVector* GetNotes() { return &_mediationNotes; }
    ReferralTypes GetReferralType() { return _referalSource; }

    DisputeProcessStates GetState() { return _processState; }
    DisputeProcessInternalStates GetInternalState() { return _processInternalState; }
    bool GetRequiresSpanish() { return _requiresSpanish; }
    MediationSessionVector *getMediationSessionVector() {return &_mediationSessionVector;}

    bool GetInfoOnly() { return _infoOnly; }
    void SetInfoOnly(bool infoOnly) { _infoOnly = infoOnly; }
    InquiryTypes GetInquiryType() { return _inquiryType; }
    void SetInquiryTypes(InquiryTypes type) { _inquiryType = type; }

    bool GetIsCourtCase() { return _isCourtCase; }
    QDateTime GetCourtDate() { return _courtDate; }
    CourtCaseTypes GetCourtType() { return _courtCaseType; }
    CourtOrderTypes GetCourtOrderType() { return _courtOrderType; }
    QDateTime GetCourtOrderExpiration() { return _courtOrderExpiration; }

    bool GetIsShuttle() { return _isShuttle; }
    void SetIsShuttle(bool isShuttle) { _isShuttle = isShuttle; }

    void SetIsCourtCase(bool isCourt) { _isCourtCase = isCourt; }
    void SetCourtDate(QDateTime courtDate) { _courtDate = courtDate; _isCourtCase = true; }
    void SetCourtType(CourtCaseTypes caseType) { _courtCaseType = caseType; }
    void SetCourtOrderType(CourtOrderTypes orderType) { _courtOrderType = orderType; }
    void SetCourtOrderExpiration(QDateTime expiration) { _courtOrderExpiration = expiration; }

    void SetDisputeType(DisputeTypes type) { _disputeType = type; }
    void SetCountyId(CountyIds countyId) { _countyOfMediation = countyId; }
    void AddNote(QString note) { _mediationNotes.push_back(new Note(note)); }
    void SetReferralType(ReferralTypes type) { _referalSource = type; }

    void SetState(DisputeProcessStates state) { _processState = state; }
    void SetInternalState(DisputeProcessInternalStates state) { _processInternalState = state; }
    void SetRequiresSpanish(bool requiresSpanish) { _requiresSpanish = requiresSpanish; }
    void setMediationSessionVector(MediationSessionVector *value) {if(value) _mediationSessionVector = *value;}

    void SetSessionType(SessionTypes type) { _sessionType = type; }
    SessionTypes GetSessionType() { return _sessionType; }

    // Helpers
    int GetAffectedChildrenCount();
    void addMediation();
    void removeParty(int value);
    void updateClientSessions(int value);

    // Report Helpers
    bool IsSettled();

private:

    PartyVector _parties;

    DisputeTypes _disputeType;

    // NEW! 7/14/2014
    SessionTypes _sessionType;

    // NEW!  7/4/2014
    DisputeProcessInternalStates _processInternalState;

    DisputeProcessStates _processState;

    CountyIds _countyOfMediation;

    MediationNotesVector _mediationNotes;

    ReferralTypes _referalSource;

    bool _requiresSpanish;

    MediationSessionVector _mediationSessionVector;

    // NEW!  7/4/2014
    InquiryTypes _inquiryType;
    bool _infoOnly;

    // NEW!  7/4/2014
    bool _isShuttle;

    // Court Stuff - ALL NEW 7/4/2014
    bool _isCourtCase;
    QDateTime _courtDate;
    enum CourtCaseTypes _courtCaseType;
    enum CourtOrderTypes _courtOrderType;
    QDateTime _courtOrderExpiration;

    // NEW!  7/12/2014
    bool _isPhoneConciliation;  // sessions held over phone
    bool _isFacilitation;       // DRC is hosting only

};

#endif // MEDIATIONPROCESS_H
