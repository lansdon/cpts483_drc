#include "reswareport.h"
#include "drctypes.h"
#include <QPrinter>
#include <QDesktopServices>
#include <QDebug>
#include <QTextBlock>
#include <QTextTable>
#include <QTextEdit>
#include <QDate>
#include "DRCModels.h"


const QString DEF_PDF_PATH = "RES_WA_REPORT.pdf";

const int CasesTableRows = 19, CasesTableCols = 14;

enum CasesTableIndices
{
    CT_NONE,
    CT_SMALL_CLAIMS,
    CT_SMALL_CLAIMS_SETTLED,
    CT_SMALL_CLAIMS_PERC,
    CT_OTHER_DIST_COURT,
    CT_OTHER_DIST_COURT_SETTLED,
    CT_OTHER_DIST_COURT_PERC,
    CT_JUVENIILE_COURT,
    CT_JUVENIILE_COURT_SETTLED,
    CT_JUVENIILE_COURT_PERC,
    CT_SUPERIOR_COURT,
    CT_SUPERIOR_COURT_SETTLED,
    CT_SUPERIOR_COURT_PERC,
    CT_OTHER_CASES,
    CT_OTHER_CASES_SETTLED,
    CT_OTHER_CASES_PERC,
    CT_TOTAL_CASES,
    CT_TOTAL_CASES_SETTLED,
    CT_TOTAL_CASES_PERC,
};
enum CasesTableHeaders
{
    CT_H_NONE,
    CT_H_PARENTING,
    CT_H_DISOLUTION,
    CT_H_FORECLOSURE,
    CT_H_TENANT,
    CT_H_BUSINESS,
    CT_H_WORKPLACE,
    CT_H_NEIGHBOR,
    CT_H_VICTIM,
    CT_H_PARENT,
    CT_H_SCHOOL,
    CT_H_ELDER,
    CT_H_OTHER,
    CT_H_TOTAL
};

ResWaReport::ResWaReport(MediationProcessVector *processes)
    : _processes(processes)
    , _q1Yes(0)
    , _q1No(0)
    , _q1Somewhat(0)
    , _q2Yes(0)
    , _q2No(0)
    , _q2Somewhat(0)
    , _q3Yes(0)
    , _q3No(0)
    , _q3Somewhat(0)
    , _q4Yes(0)
    , _q4No(0)
    , _q4Somewhat(0)
    , _q5Yes(0)
    , _q5No(0)
    , _q5Somewhat(0)
    , _q6Yes(0)
    , _q6No(0)
    , _q6Somewhat(0)
{

    _headerFormat.setFontPointSize(12);
    _tableTextFormat.setFontPointSize(10);
    _tableCellBlue.setBackground(QColor("#C2E0FF"));
    _tableIndexDark.setBackground(QColor("#e0e0e0"));
    _tableIndexLight.setBackground(QColor("#eeeee0"));

    // Init case table matrix with zeros.
    for(auto row = 0; row < CasesTableRows; ++row)
        _casesTable.push_back({0,0,0,0,0,0,0,0,0,0,0,0,0,0});

}

void ResWaReport::OpenReportPDF()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(DEF_PDF_PATH)))
        qDebug() << "Error opening RESWA PDF";

}


///////////////// Report Builder ///////////////////
// Primary call
void ResWaReport::BuildReport()
{
    _report = new QTextDocument();
    _report->begin();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(DEF_PDF_PATH);

    QTextCursor cursor(_report);

    // Header - User entered data
    BuildHeaderSection(cursor);

    // 1. Cases and number of settled cases
    BuildCasesSection(cursor);

    // 2. CALLS (Information, Intake and referral calls)
    BuildCallsSection(cursor);

    // 3. CONTACTS (proactive outreach events)
    BuildContactsSection(cursor);

    // 4. TRAINING & IN-SERVICES
    BuildTrainingSection(cursor);

    // 5. PEOPLE SERVED
    BuildPeopleServedSection(cursor);

    // 6. PEOPLE REACHED VIA OUTREACH EFFORTS
    BuildOutreachSection(cursor);

    // 7. VOLUNTEER STAFF
    BuildStaffSection(cursor);

    // 8. CLIENT EVALUATIONS
    BuildEvaluationSection(cursor);



    _report->end();

    _report->print(&printer);


    OpenReportPDF();
}
///////////////// Report Builder - INTERNAL ///////////////////
// These functions build the different sections of the report
///////////////////////////////////////////////////////////////
void ResWaReport::TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* textFormat, QTextTableCellFormat* cellFormat)
{
    if(!textFormat) textFormat = &_tableTextFormat;

    auto cell = table->cellAt(row, col);
    if(cellFormat)
        cell.setFormat(*cellFormat);
    auto cellCursor = cell.firstCursorPosition();
    cellCursor.insertText(txt, *textFormat);
}

void ResWaReport::BuildHeaderSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\nEVENTS\n", _headerFormat);
    cursor.insertText("1) CASES and Number of SETTLED CASES\n", _tableTextFormat);

}

void ResWaReport::BuildCasesSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 15);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    constraints << QTextLength(QTextLength::PercentageLength, 7);
    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(CasesTableRows, CasesTableCols, tableFormat);
    // HEADERS
    TextToCell(table, CT_TOTAL_CASES_SETTLED, 0, "Cases Settled");
    TextToCell(table, CT_TOTAL_CASES_PERC, 0, "Percentage of total cases settled");
    TextToCell(table, 0, CT_H_PARENTING, "Parenting Plans");
    TextToCell(table, 0, CT_H_DISOLUTION, "Disolution");
    TextToCell(table, 0, CT_H_FORECLOSURE, "Foreclosure");
    TextToCell(table, 0, CT_H_TENANT, "Tenant Landlord");
    TextToCell(table, 0, CT_H_BUSINESS, "Business");
    TextToCell(table, 0, CT_H_WORKPLACE, "Workplace");
    TextToCell(table, 0, CT_H_NEIGHBOR, "Neighbor");
    TextToCell(table, 0, CT_H_VICTIM, "Victim Offender");
    TextToCell(table, 0, CT_H_PARENT, "Parent Teen");
    TextToCell(table, 0, CT_H_SCHOOL, "School");
    TextToCell(table, 0, CT_H_ELDER, "Elder");
    TextToCell(table, 0, CT_H_OTHER, "Other");
    TextToCell(table, 0, CT_H_TOTAL, "Total");
    // ROW INDICES
    TextToCell(table, CT_SMALL_CLAIMS , 0, "Small claims court cases", nullptr, &_tableIndexDark);
    TextToCell(table, CT_SMALL_CLAIMS_SETTLED, 0, "Small Claims Court cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_SMALL_CLAIMS_PERC, 0, "Percentage of Small Claims cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_OTHER_DIST_COURT, 0, "Other District Cout cases");
    TextToCell(table, CT_OTHER_DIST_COURT_SETTLED, 0, "Other District Cout cases settled");
    TextToCell(table, CT_OTHER_DIST_COURT_PERC, 0, "Percentage of district court cases settled");
    TextToCell(table, CT_JUVENIILE_COURT, 0, "Juvenile Court cases", nullptr, &_tableIndexDark);
    TextToCell(table, CT_JUVENIILE_COURT_SETTLED, 0, "Juvenile cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_JUVENIILE_COURT_PERC, 0, "Percentage of Juvenile cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_SUPERIOR_COURT, 0, "Superior Court cases");
    TextToCell(table, CT_SUPERIOR_COURT_SETTLED, 0, "Superior Court cases settled");
    TextToCell(table, CT_SUPERIOR_COURT_PERC, 0, "Percentage of Superior cases settled");
    TextToCell(table, CT_OTHER_CASES, 0, "Other cases", nullptr, &_tableIndexDark);
    TextToCell(table, CT_OTHER_CASES_SETTLED, 0, "Other cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_OTHER_CASES_PERC, 0, "Percentage of Other cases settled", nullptr, &_tableIndexDark);
    TextToCell(table, CT_TOTAL_CASES, 0, "Total cases");

    // POPULATE CELLS FROM MATRIX
    for (auto row = 1; row < CasesTableRows; ++row)
        for (auto col = 1; col < CasesTableCols; ++col)
            TextToCell(table, row, col, QString::number(_casesTable[row][col]),nullptr, &_tableCellBlue);

}


// 2)  CALLS
void ResWaReport::BuildCallsSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n2) CALLS (Information, intake, and referal calls)\n", _headerFormat);

    cursor.insertText("Total calls: " + QString::number(CalculateTotalCalls()) + "\n\n");
}

// 3) CONTACTS
void ResWaReport::BuildContactsSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n3) Contacts (proactive outreach events\n", _headerFormat);
    cursor.insertText("!! This information is not available !!\n", _headerFormat);
}

// 4) TRAINING
void ResWaReport::BuildTrainingSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n4) TRAINING & IN-SERVICES\n");

    // VALUES
    int numTrainings;
    int numAttendingTrainings;
    CalculateTraining(numTrainings, numAttendingTrainings);
    cursor.insertText("\t\t\t# of trainings: " + QString::number(numTrainings) + "\n");
    cursor.insertText("\t\t\t# attending trainings: " + QString::number(numAttendingTrainings) + "\n");


}

void ResWaReport::BuildPeopleServedSection(QTextCursor& cursor)
{

    CalculatePeople();
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n5) People Served\n", _headerFormat);
    cursor.insertText("A.\t# of people served by telephone:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numByPhone) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildByPhone) + "\n", _headerFormat);
    cursor.insertText("B.\t# of people served by conflict coaching:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numByCoaching) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildByCoaching) + "\n", _headerFormat);
    cursor.insertText("C.\t# of people served by telephone concilliation:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numByPhoneConcilliation) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildByPhoneConcilliation) + "\n", _headerFormat);
    cursor.insertText("D.\t# of people served by mediation sessions:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numBySessions) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildBySessions) + "\n", _headerFormat);
    cursor.insertText("E.\t# of people served by facilliation sessions:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numBySessionFacilliation) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildBySessionFacilliation) + "\n", _headerFormat);
    cursor.insertText("F.\t# of people INDIRECTLY served by phone, concilliation, mediation, facilliation:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numIndirectly) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildIndirectly) + "\n", _headerFormat);
    cursor.insertText("G.\t# of people served by training and in-service:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numByTraining) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildByTraining) + "\n", _headerFormat);
    cursor.insertText("H.\t# of additional people served:\n", _headerFormat);
    cursor.insertText("\t\t\tAll people Served: " + QString::number(_numAdditionalServed) + "\n", _headerFormat);
    cursor.insertText("\t\t\tChildren Served: " + QString::number(_numChildAdditionalServed) + "\n", _headerFormat);

}

void ResWaReport::BuildOutreachSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n6) Outreach \n", _headerFormat);

    cursor.insertText("\n\t !! INFORMATION UNAVAILABLE !! \n", _headerFormat);
}

void ResWaReport::BuildStaffSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n7) BuildStaffSection\n", _headerFormat);

    cursor.insertText("\n\t !! INFORMATION UNAVAILABLE !! \n", _headerFormat);
}

void ResWaReport::BuildEvaluationSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n8) Evaluations\n", _headerFormat);

    // fair
    cursor.insertText("\tMediators fair and impartial?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q1Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q1No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q1Somewhat) + "\n"));

    // improved situation
    cursor.insertText("\tSituation Improved By Mediation?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q2Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q2No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q2Somewhat) + "\n"));

    // helped you communicate
    cursor.insertText("\tHelped to communicate with other party?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q3Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q3No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q3Somewhat) + "\n"));

    // helped understand other point view
    cursor.insertText("\tHelped to better understand the issues?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q4Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q4No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q4Somewhat) + "\n"));

    // Would recommend to someone else
    cursor.insertText("\tRecommend mediation to others?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q5Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q5No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q5Somewhat) + "\n"));

    // was agreement reached
    cursor.insertText("\tDid you reach an agreement?\n", _headerFormat);
    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q6Yes) + "\n"));
    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q6No) + "\n"));
    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q6Somewhat) + "\n"));

}

int ResWaReport::CalculateTotalCalls()
{
#warning RESWA BL UNIMPLEMENTED!
    return -666;
}

void ResWaReport::AddMPToCasesTable(DisputeTypes disputeType, CourtCaseTypes courtType, bool settled)
{
    CasesTableIndices row;
    if(courtType == COURT_T_SMALL_CLAIMS) row = CT_SMALL_CLAIMS;
    else if(courtType == COURT_T_OTHER)
    {
    }

    switch(disputeType)
    {
    case DISPUTE_T_PARENTING_PLAN:
        _casesTable[row][CT_H_PARENTING]++;
        if(settled) _casesTable[row+1][CT_H_PARENTING]++;
        break;
    case DISPUTE_T_TENANT:
        _casesTable[row][CT_H_TENANT]++;
        if(settled) _casesTable[row+1][CT_H_TENANT]++;
        break;
    case DISPUTE_T_PROPERTY_BUSINESS:
        _casesTable[row][CT_H_BUSINESS]++;
        if(settled) _casesTable[row+1][CT_H_BUSINESS]++;
        break;
    case DISPUTE_T_WORKPLACE:
        _casesTable[row][CT_H_WORKPLACE]++;
        if(settled) _casesTable[row+1][CT_H_WORKPLACE]++;
        break;
    case DISPUTE_T_NEIGHBORHOOD:
        _casesTable[row][CT_H_NEIGHBOR]++;
        if(settled) _casesTable[row+1][CT_H_NEIGHBOR]++;
        break;
    case DISPUTE_T_PARENT_TEEN:
        _casesTable[row][CT_H_PARENT]++;
        if(settled) _casesTable[row+1][CT_H_PARENT]++;
        break;
    default:
        _casesTable[row][CT_H_OTHER]++;
        if(settled) _casesTable[row+1][CT_H_OTHER]++;
        break;
    }


}

void ResWaReport::CalculateCasesTable()
{
    foreach(MediationProcess* mp,  *_processes)
    {
        AddMPToCasesTable(mp->GetDisputeType(), mp->GetCourtType(), mp->IsSettled());
    }
}


// 4) TRAININGS
int ResWaReport::GetNumberAttending(MediationSession* session)
{
    int result = 0;
    if(session->getObserver1().length()) ++result;
    if(session->getObserver2().length()) ++result;
    if(session->getMediator1().length()) ++result;
    if(session->getMediator2().length()) ++result;

    foreach(ClientSessionData* csData, *session->getClientSessionDataVector())
    {
        ++result;  // add one for the client
        if(csData->getAttyDidAttend()) ++result;
        result += (int)csData->getSupport();
    }
    return result;
}

void ResWaReport::CalculateTraining(int& numTrainings, int& numAttendingTraining)
{
    numTrainings = numAttendingTraining = 0;

    foreach(MediationProcess* mp,  *_processes)
    {
        int curAttendees = 0;
        bool foundTrainee = false;
        foreach(MediationSession* session, *mp->getMediationSessionVector())
        {
            if(session->getObserver1().length())
            {
                foundTrainee = true;
                ++numTrainings;
            }
            if(session->getObserver2().length())
            {
                foundTrainee = true;
                ++numTrainings;
            }
            curAttendees += GetNumberAttending(session);
        }

        if(foundTrainee)
        {
            numAttendingTraining += curAttendees;
        }
    }
}

void ResWaReport::CalculatePeople()
{
#warning RESWA BL UNIMPLEMENTED
    _numByPhone
    = _numChildByPhone
    = _numByCoaching
    = _numChildByCoaching
    = _numByPhoneConcilliation
    = _numChildByPhoneConcilliation
    = _numBySessions
    = _numChildBySessions
    = _numBySessionFacilliation
    = _numChildBySessionFacilliation
    = _numIndirectly
    = _numChildIndirectly
    = _numByTraining
    = _numChildByTraining
    = _numAdditionalServed
    = _numChildAdditionalServed = 0;

}