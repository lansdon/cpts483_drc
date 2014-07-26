#include "mediationprocess.h"

#include <sstream>
#include "DRCModels.h"
#include "drctypes.h"
#include <random>
#include "DBBaseObject.h"

const QString DEF_PDF_PATH = "MEDIATION_PROCESS_REPORT.pdf";

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
    , _disputeType(DISPUTE_T_NONE)
    , _inquiryType(INQUIRY_T_NONE)
    , _processInternalState(PROCESS_INTERNAL_STATE_NONE)
    , _processState(PROCESS_STATE_NONE)
    , _countyOfMediation(COUNTY_BENTON)
    , _referalSource(REFERRAL_T_NONE)
    , _requiresSpanish(false)
    , _isCourtCase(false)
    , _courtCaseType(COURT_T_NONE)
    , _infoOnly(false)
    , _isShuttle(false)
    , _sessionType(MEDIATION_SESSION)
    , _mediationClause(false)
{
    _courtDate = QDate::currentDate();
}


MediationProcess::~MediationProcess()
{
}

void MediationProcess::OpenReportPDF()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(DEF_PDF_PATH)))
        qDebug() << "Error opening MEDIATION_PROCESS_REPORT.pdf";
}

///////////////// Print PDF ///////////////////
void MediationProcess::PrintMediation()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(DEF_PDF_PATH);

    BuildReport();

    _report->print(&printer);
}


///////////////// Report Builder ///////////////////
// Primary call
void MediationProcess::BuildReport()
{
    _report = new QTextDocument();
    _report->begin();

    QTextCursor cursor(_report);

    // Header - User entered data
    BuildHeaderSection(cursor);

    // 1. General Information:  Inquiry, Mediation and Session information
    BuildGeneralInfoSection(cursor);

    // 2.  Party Information:  Party member address, phone and attorney information
    BuildPartyInfoSection(cursor);

    // 3.  Session Information:  Schedule, client and mediation information
    BuildSessionInfoSection(cursor);

    // 4.  Notes Information:  Just Notes.
    BuildNotesSesction(cursor);

    _report->end();    

    OpenReportPDF();
}

///////////////// Report Builder - INTERNAL ///////////////////
// These functions build the different sections of the report
///////////////////////////////////////////////////////////////
void MediationProcess::TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* textFormat, QTextTableCellFormat* cellFormat)
{
    if(!textFormat) textFormat = &_tableTextFormat;

    auto cell = table->cellAt(row, col);
    if(cellFormat)
        cell.setFormat(*cellFormat);
    auto cellCursor = cell.firstCursorPosition();
    cellCursor.insertText(txt, *textFormat);
}

void MediationProcess::BuildHeaderSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();  //  Is this necessary?
    cursor.insertText("\nMediation\n", _headerFormat);
    cursor.insertText("Inquiry, Mediation and Session types and statuses\n", _tableTextFormat);
}

void MediationProcess::BuildGeneralInfoSection(QTextCursor &cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n========== General Information ==========", _tableTextFormat);

    QString CurrentStatus = "\nCurrent Status:\t";
    CurrentStatus += StringForDisputeProcessStates(_processState);
    CurrentStatus += "\n -Last Activity:\t";
    CurrentStatus += m_updated.toString();
    CurrentStatus += "\n -Creation Date:\t";
    CurrentStatus += m_created.currentDateTime().toString();
    cursor.insertText(CurrentStatus, _tableTextFormat);

    QString InquiryType = "\nInquiry Type:\t";
    InquiryType += StringForInquiryTypes(_inquiryType);
    cursor.insertText(InquiryType, _tableTextFormat);

    QString CourtCase = "\nCourt Case:\t";
    CourtCase += (_isCourtCase == true ? "Yes" : "No");
    cursor.insertText(CourtCase, _tableTextFormat);

    QString InfoOnly = "\nInfo Only:\t";
    InfoOnly += (_infoOnly == true ? "Yes" : "No");
    cursor.insertText(InfoOnly, _tableTextFormat);

    QString ReferralSource = "\nReferral Source:\t";
    ReferralSource += StringForReferralTypes(_referalSource);
    cursor.insertText(ReferralSource, _tableTextFormat);

    QString MediationType = "\nMediation Type:\t";
    MediationType += StringForDisputeTypes(_disputeType);
    cursor.insertText(MediationType, _tableTextFormat);

    QString RequiresSpanish = "\nRequires Spanish:\t";
    RequiresSpanish += (_requiresSpanish == true ? "Yes" : "No");
    cursor.insertText(RequiresSpanish, _tableTextFormat);

    QString CountyofMediation = "\nCounty of Mediation:\t";
    CountyofMediation += StringForCountyIds(_countyOfMediation);
    cursor.insertText(CountyofMediation, _tableTextFormat);

    QString SessionType = "\nSession Type:\t";
    SessionType += StringForSessionTypes(_sessionType);
    cursor.insertText(SessionType, _tableTextFormat);

    QString CourtCaseType = "\nCourt Case Type:\t";
    CourtCaseType += StringForCourtTypes(_courtCaseType);
    cursor.insertText(CourtCaseType, _tableTextFormat);

    QString CourtDate = "\nCourt Date:\t";
    CourtDate += _courtDate.toString();
    cursor.insertText(CourtDate, _tableTextFormat);

    QString CourtOrderType = "\nCourt Order:\t";
    CourtOrderType += _courtOrder;
    cursor.insertText(CourtOrderType, _tableTextFormat);

//    QString CourtOrderExpires = "\nCourt Order Expires:\t";
//    CourtOrderExpires += _courtOrderExpiration.toString();
//    cursor.insertText(CourtOrderExpires, _tableTextFormat);\

}

void MediationProcess::BuildPartyInfoSection(QTextCursor &cursor)
{
    for (int i = 0; i < _parties.size(); i++)
    {
        QString ClientHeader = "\n========== ";
        ClientHeader += "Client ";
        ClientHeader += QString::number(i + 1);
        ClientHeader += " ==========";
        cursor.insertText(ClientHeader, _tableTextFormat);
        _parties.at(i)->BuildToPDF(cursor);
    }
}

void MediationProcess::BuildSessionInfoSection(QTextCursor &cursor)
{
    for (int i = 0; i < _mediationSessionVector.size(); i++)
    {
        QString ClientHeader = "\n========== ";
        ClientHeader += "Session ";
        ClientHeader += QString::number(i + 1);
        ClientHeader += " ==========";
        cursor.insertText(ClientHeader, _tableTextFormat);
        _mediationSessionVector.at(i)->BuildToPDF(cursor);
    }
}

void MediationProcess::BuildNotesSesction(QTextCursor &cursor)
{
    QString NotesHeader = "\n============================ Notes ===========================\n\n";
    NotesHeader += "============= Creation Date ==================== Note =============\n";
    cursor.insertText(NotesHeader, _tableTextFormat);
    for (int i = 0; i < _mediationNotes.size(); i++)
    {
        std::cout << i << std::endl;

//        NotesHeader += "Note ";
//        NotesHeader += QString::number(i + 1);
//        NotesHeader += " ==========";

        _mediationNotes.at(i)->BuildToPDF(cursor);
    }
}

QString MediationProcess::ColumnNames()
{
    QString column_names = QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, ")
            .arg(QString("Process_id"))
            .arg(QString("DisputeType"))
            .arg(QString("CreationDate"))
            .arg(QString("UpdatedDate"))
            .arg(QString("CreationDateTime"))
            .arg(QString("UpdatedDateTime"))
            .arg(QString("DisputeState"))
            .arg(QString("DisputeInternalState"))
            .arg(QString("DisputeCounty"));

    column_names += QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, %10")
            .arg(QString("ReferalSource"))
            .arg(QString("InquiryType"))
            .arg(QString("InfoOnly"))
            .arg(QString("IsCourtCase"))
            .arg(QString("CourtDate"))
            .arg(QString("CourtCaseType"))
            .arg(QString("CourtOrderType"))
            .arg(QString("TranslatorRequired"))
            .arg(QString("SessionType"))
            .arg(QString("MediationClause"));

    QString toReturn = QString("(%1)")
            .arg(column_names);

    return toReturn;
}

QString MediationProcess::Parse()
{


    // UPDATED 7-14-14 for new schema
    QString column_values = QString("%1, %2, '%3', '%4', '%5', '%6', %7, %8, %9, ")
            .arg(QString("null"))
            .arg(QString::number(this->GetDisputeType()))
            .arg(this->GetCreatedDate().toString("yyyy-MM-dd"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd"))
            .arg(this->GetCreatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(QString::number(this->GetState()))
            .arg(QString::number(this->GetInternalState()))
            .arg(QString::number(this->GetCountyId()));

    column_values += QString("%1, '%2', '%3', '%4', '%5', %6, '%7', '%8', '%9', %10")
            .arg(QString::number(this->GetReferralType()))
            .arg(QString::number(this->GetInquiryType()))
            .arg(this->GetInfoOnly())
            .arg(this->GetIsCourtCase())
            .arg(this->GetCourtDate().toString("yyyy-MM-dd"))
            .arg(QString::number(this->GetCourtType()).replace("'", "''"))
            .arg(this->GetCourtOrder().replace("'", "''"))
            .arg(QString::number(this->GetRequiresSpanish()))
            .arg(QString::number(this->GetSessionType()))
            .arg(this->getMediationClause());

//    QString toReturn = QString("(%1) VALUES(%2)")
//        .arg(column_names)
//        .arg(column_values);

    return column_values;
}

QString MediationProcess::UpdateParse()
{
    //Updated 7-14-14 for new schema
    QString toUpdate = QString("DisputeType = %1, UpdatedDate = '%2', UpdatedDateTime = '%3', DisputeState = %4, DisputeInternalState = %5, DisputeCounty = %6, ")
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

    toUpdate += QString("CourtDate = '%1', CourtCaseType = %2, CourtOrderType = '%3', TranslatorRequired = '%4', SessionType = %5, MediationClause = '%6'")
            .arg(this->GetCourtDate().toString("yyyy-MM-dd"))
            .arg(QString::number(this->GetCourtType()))
            .arg(this->GetCourtOrder().replace("'", "''"))
            .arg(this->GetRequiresSpanish())
            .arg(QString::number(this->GetSessionType()))
            .arg(this->getMediationClause());

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
    {
        //if(session->getOutcome() == SESSION_OUTCOME_AGREEMENT || session->getOutcome() == SESSION_OUTCOME_PROBLEM_SOLVING || session->getOutcome() == SESSION_OUTCOME_SELF_RESOLVED)
        // I agrue that self-resolved means the parties solved their problem without the DRC's help, so that doesn't count as the DRC settleing it.
        if(session->getOutcome() == SESSION_OUTCOME_AGREEMENT || session->getOutcome() == SESSION_OUTCOME_PROBLEM_SOLVING)
        {
            return true;
        }
    }

    return false;
}

void MediationProcess::AddParty(Party *party)
{
     _parties.push_back(party);
     for(int i = 0; i < (int)_mediationSessionVector.size(); i++)
     {
         MediationSession *temp = _mediationSessionVector.at(i);
         if(temp->getClientSessionDataVector()->size() < _parties.size())
            temp->addClientSessionData(new ClientSessionData());
     }
}
