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

/*!
 * \brief The MediationProcess class
 */
class MediationProcess : public DBBaseObject
{
public:
    MediationProcess();
    virtual ~MediationProcess();

    // Required Overrides
    /*!
     * \brief Parse
     * \return
     */
    QString Parse();
    QString ColumnNames();
    /*!
     * \brief UpdateParse
     * \return
     */
    QString UpdateParse();
    /*!
     * \brief table
     * \return
     */
    QString table();
    /*!
     * \brief DuplicateQuery
     * \return
     */
    QString DuplicateQuery();
    /*!
     * \brief SearchQuery
     * \return
     */
    QString SearchQuery();
    /*!
     * \brief GetIdRowName
     * \return
     */
    QString GetIdRowName();
    /*!
     * \brief SampleData
     * \return
     */
    static MediationProcess* SampleData();

    // Accessors
    /*!
     * \brief GetParties
     * \return
     */
    PartyVector* GetParties() { return &_parties; }
    /*!
     * \brief GetPartyAtIndex
     * \param index
     * \return
     */
    Party* GetPartyAtIndex(unsigned int index) { return _parties.size() > index ? _parties[index] : nullptr; }
    /*!
     * \brief AddParty
     * \param party
     */
    void AddParty(Party* party);
    /*!
     * \brief GetDisputeType
     * \return
     */
    DisputeTypes GetDisputeType() { return _disputeType; }
    /*!
     * \brief GetCountyId
     * \return
     */
    CountyIds GetCountyId() { return _countyOfMediation; }
    /*!
     * \brief GetNotes
     * \return
     */
    MediationNotesVector* GetNotes() { return &_mediationNotes; }
    /*!
     * \brief GetReferralType
     * \return
     */
    ReferralTypes GetReferralType() { return _referalSource; }
    /*!
     * \brief GetState
     * \return
     */
    DisputeProcessStates GetState() { return _processState; }
    /*!
     * \brief GetInternalState
     * \return
     */
    DisputeProcessInternalStates GetInternalState() { return _processInternalState; }
    /*!
     * \brief GetRequiresSpanish
     * \return
     */
    bool GetRequiresSpanish() { return _requiresSpanish; }
    /*!
     * \brief getMediationSessionVector
     * \return
     */
    MediationSessionVector *getMediationSessionVector() {return &_mediationSessionVector;}
    /*!
     * \brief GetInfoOnly
     * \return
     */
    bool GetInfoOnly() { return _infoOnly; }
    /*!
     * \brief SetInfoOnly
     * \param infoOnly
     */
    void SetInfoOnly(bool infoOnly) { _infoOnly = infoOnly; }
    /*!
     * \brief GetInquiryType
     * \return
     */
    InquiryTypes GetInquiryType() { return _inquiryType; }
    /*!
     * \brief SetInquiryTypes
     * \param type
     */
    void SetInquiryTypes(InquiryTypes type) { _inquiryType = type; }
    /*!
     * \brief GetIsCourtCase
     * \return
     */
    bool GetIsCourtCase() { return _isCourtCase; }
    /*!
     * \brief GetCourtDate
     * \return
     */
    QDate GetCourtDate() { return _courtDate; }
    /*!
     * \brief GetCourtType
     * \return
     */
    CourtCaseTypes GetCourtType() { return _courtCaseType; }
    /*!
     * \brief GetCourtOrder
     * \return
     */
    QString GetCourtOrder() { return _courtOrder; }
    /*!
     * \brief GetIsShuttle
     * \return
     */
    bool GetIsShuttle() { return _isShuttle; }
    /*!
     * \brief SetIsShuttle
     * \param isShuttle
     */
    void SetIsShuttle(bool isShuttle) { _isShuttle = isShuttle; }
    /*!
     * \brief SetIsCourtCase
     * \param isCourt
     */
    void SetIsCourtCase(bool isCourt) { _isCourtCase = isCourt; }
    /*!
     * \brief SetCourtType
     * \param caseType
     */
    void SetCourtType(CourtCaseTypes caseType) { _courtCaseType = caseType; }
    /*!
     * \brief SetCourtOrder
     * \param orderType
     */
    void SetCourtOrder(QString orderType) { _courtOrder = orderType; }
    /*!
     * \brief SetDisputeType
     * \param type
     */
    void SetDisputeType(DisputeTypes type) { _disputeType = type; }
    /*!
     * \brief SetCountyId
     * \param countyId
     */
    void SetCountyId(CountyIds countyId) { _countyOfMediation = countyId; }
    /*!
     * \brief AddNote
     * \param note
     */
    void AddNote(QString note) { _mediationNotes.push_back(new Note(note)); }
    /*!
     * \brief SetCourtDate
     * \param CourtDate
     */
    void SetCourtDate(QDate CourtDate) { _courtDate = CourtDate; }
    /*!
     * \brief SetReferralType
     * \param type
     */
    void SetReferralType(ReferralTypes type) { _referalSource = type; }
    /*!
     * \brief SetState
     * \param state
     */
    void SetState(DisputeProcessStates state) { _processState = state; }
    /*!
     * \brief SetInternalState
     * \param state
     */
    void SetInternalState(DisputeProcessInternalStates state) { _processInternalState = state; }
    /*!
     * \brief SetRequiresSpanish
     * \param requiresSpanish
     */
    void SetRequiresSpanish(bool requiresSpanish) { _requiresSpanish = requiresSpanish; }
    /*!
     * \brief setMediationSessionVector
     * \param value
     */
    void setMediationSessionVector(MediationSessionVector *value) {if(value) _mediationSessionVector = *value;}
    /*!
     * \brief SetSessionType
     * \param type
     */
    void SetSessionType(SessionTypes type) { _sessionType = type; }
    /*!
     * \brief GetSessionType
     * \return
     */
    SessionTypes GetSessionType() { return _sessionType; }
    /*!
     * \brief SetStateMessage
     * \param message
     */
    void SetStateMessage(QString message) { _stateMessage = message; }
    /*!
     * \brief GetStateMessage
     * \return
     */
    QString GetStateMessage() { return _stateMessage; }

    void setMediationClause(bool value) { _mediationClause = value; }
    bool getMediationClause() const { return _mediationClause; }
    void setPrintCourtDate(bool value) { _printCourtDate = value; }
    bool getPrintCourtDate() const { return _printCourtDate; }

    // Helpers
    /*!
     * \brief GetAffectedChildrenCount
     * \return
     */
    int GetAffectedChildrenCount();
    /*!
     * \brief addMediation
     */
    void addMediation();
    /*!
     * \brief removeParty
     * \param value
     */
    void removeParty(int value);
    /*!
     * \brief updateClientSessions
     * \param value
     */
    void updateClientSessions(int value);

    // Report Helpers
    /*!
     * \brief IsSettled
     * \return
     */
    bool IsSettled();

    // External call to print our Mediation
    /*!
     * \brief PrintMediation
     */
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
    /*!
     * \brief TextToCell
     * \param table
     * \param row
     * \param col
     * \param txt
     * \param format
     * \param cellFormat
     */
    void TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* format = nullptr, QTextTableCellFormat* cellFormat = nullptr);

    PartyVector _parties;
    DisputeTypes _disputeType;
    SessionTypes _sessionType;
    DisputeProcessInternalStates _processInternalState;
    DisputeProcessStates _processState;
    CountyIds _countyOfMediation;
    MediationNotesVector _mediationNotes;
    ReferralTypes _referalSource;
    bool _requiresSpanish;
    bool _mediationClause;
    bool _printCourtDate;
    MediationSessionVector _mediationSessionVector;
    InquiryTypes _inquiryType;
    bool _infoOnly;
    bool _isShuttle;
    bool _isCourtCase;
    QDate _courtDate;
    enum CourtCaseTypes _courtCaseType;
    QString _courtOrder;
    QString _stateMessage;  // Message set by BL explaining how to advance to next state.

    ///////////////// Report Builder ///////////////////
    /*!
     * \brief BuildReport
     */
    void BuildReport();         // Primary call

    // Build PDF
    /*!
     * \brief OpenReportPDF
     */
    void OpenReportPDF();

    ///////////////// Report Builder - INTERNAL ///////////////////
    // These functions build the different sections of the report
    ///////////////////////////////////////////////////////////////
    /*!
     * \brief BuildHeaderSection
     * \param cursor
     */
    void BuildHeaderSection(QTextCursor& cursor);
    /*!
     * \brief BuildGeneralInfoSection
     * \param cursor
     */
    void BuildGeneralInfoSection(QTextCursor& cursor);
    /*!
     * \brief BuildPartyInfoSection
     * \param cursor
     */
    void BuildPartyInfoSection(QTextCursor& cursor);
    /*!
     * \brief BuildSessionInfoSection
     * \param cursor
     */
    void BuildSessionInfoSection(QTextCursor& cursor);
    /*!
     * \brief BuildNotesSesction
     * \param cursor
     */
    void BuildNotesSesction(QTextCursor& cursor);

};

#endif // MEDIATIONPROCESS_H
