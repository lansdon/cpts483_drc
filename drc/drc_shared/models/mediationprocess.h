#ifndef MEDIATIONPROCESS_H
#define MEDIATIONPROCESS_H

#include <vector>
#include "drctypes.h"
#include <QDate>
#include <QTextBlock>
#include <QPrinter>
#include <QDebug>
#include <QDesktopServices>
#include <QTextDocument>
#include <QTextTable>
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

    void SetStateMessage(QString message) { _stateMessage = message; }
    QString GetStateMessage() { return _stateMessage; }

    // Helpers
    int GetAffectedChildrenCount();
    void addMediation();
    void removeParty(int value);
    void updateClientSessions(int value);

    // Report Helpers
    bool IsSettled();

    // External call to print our Mediation
    void PrintMediation();



private:

    // The final report object after it's been built.
    QTextDocument* _report;

    // Text Formatters
    QTextCharFormat _headerFormat;
    QTextCharFormat _tableTextFormat;
    QTextTableCellFormat _tableCellBlue;
    QTextTableCellFormat _tableIndexDark;
    QTextTableCellFormat _tableIndexLight;

    void TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* format = nullptr, QTextTableCellFormat* cellFormat = nullptr);

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

    QString _stateMessage;  // Message set by BL explaining how to advance to next state.

    ///////////////// Report Builder ///////////////////
    void BuildReport();         // Primary call

    // Build PDF
    void OpenReportPDF();

    ///////////////// Report Builder - INTERNAL ///////////////////
    // These functions build the different sections of the report
    ///////////////////////////////////////////////////////////////
    void BuildHeaderSection(QTextCursor& cursor);
    void BuildGeneralInfoSection(QTextCursor& cursor);
    void BuildPartyInfoSection(QTextCursor& cursor);
    void BuildSessionInfoSection(QTextCursor& cursor);

};

#endif // MEDIATIONPROCESS_H
