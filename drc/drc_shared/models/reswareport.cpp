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
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(DEF_PDF_PATH);
    printer.setPageMargins(12, 8, 12, 12, QPrinter::Millimeter);

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
    CalculateCasesTable();

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

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTableFormat tableFormat;
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    TextToCell(table, 0, 0, "Total calls", &_tableTextFormat);
    TextToCell(table, 0, 1, QString::number(_totalCalls), &_tableCellBlue);
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
//    cursor.insertText("\t\t\t# of trainings: " + QString::number(numTrainings) + "\n");
//    cursor.insertText("\t\t\t# attending trainings: " + QString::number(numAttendingTrainings) + "\n");

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 35);
    constraints << QTextLength(QTextLength::PercentageLength, 35);

    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(table, 0, 0, "# of trainings (observers)", &_tableTextFormat);
    TextToCell(table, 0, 1, "# attending trainings (all people in room)", &_tableTextFormat);
    // VALUES
    TextToCell(table, 1, 0, QString::number(numTrainings), &_tableCellBlue);
    TextToCell(table, 1, 1, QString::number(numAttendingTrainings), &_tableCellBlue);
}

void ResWaReport::BuildPeopleServedSection(QTextCursor& cursor)
{
    CalculatePeople();

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n5) People Served\n", _headerFormat);

    QTextTableFormat tableFormat;
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    tableFormat.setColumnWidthConstraints(constraints);

    cursor.insertText("\nA. # of people served by telephone:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(table, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(table, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(table, 0, 1, QString::number(_numByPhone), &_tableCellBlue);
    TextToCell(table, 1, 1, QString::number(_numChildByPhone), &_tableCellBlue);


    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nB. # of people served by conflict coaching:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableB = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableB, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableB, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableB, 0, 1, QString::number(_numByCoaching), &_tableCellBlue);
    TextToCell(tableB, 1, 1, QString::number(_numChildByCoaching), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nC.# of people served by telephone concilliation:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableC = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableC, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableC, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableC, 0, 1, QString::number(_numByPhoneConcilliation), &_tableCellBlue);
    TextToCell(tableC, 1, 1, QString::number(_numChildByPhoneConcilliation), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nD. # of people served by mediation sessions:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableD = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableD, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableD, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableD, 0, 1, QString::number(_numBySessions), &_tableCellBlue);
    TextToCell(tableD, 1, 1, QString::number(_numChildBySessions), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nE. # of people served by facilliation sessions:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableE = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableE, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableE, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableE, 0, 1, QString::number(_numBySessionFacilliation), &_tableCellBlue);
    TextToCell(tableE, 1, 1, QString::number(_numChildBySessionFacilliation), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nF. # of people INDIRECTLY served by phone, concilliation, mediation, facilliation:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableF = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableF, 0, 0, "All People Indirectly Served", &_tableTextFormat);
    TextToCell(tableF, 1, 0, "Children Indirectly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableF, 0, 1, QString::number(_numIndirectly), &_tableCellBlue);
    TextToCell(tableF, 1, 1, QString::number(_numChildIndirectly), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nG. # of people served by training and in-service:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableG = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableG, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableG, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableG, 0, 1, QString::number(_numByTraining), &_tableCellBlue);
    TextToCell(tableG, 1, 1, QString::number(_numChildByTraining), &_tableCellBlue);

    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\nH. # of additional people served:\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *tableH = cursor.insertTable(2, 2, tableFormat);
    // HEADERS
    TextToCell(tableH, 0, 0, "All People Directly Served", &_tableTextFormat);
    TextToCell(tableH, 1, 0, "Children Directly Served", &_tableTextFormat);
    // VALUES
    TextToCell(tableH, 0, 1, QString::number(_numAdditionalServed), &_tableCellBlue);
    TextToCell(tableH, 1, 1, QString::number(_numChildAdditionalServed), &_tableCellBlue);
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

    QTextTableFormat tableFormat;
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33);
    constraints << QTextLength(QTextLength::PercentageLength, 33);
    constraints << QTextLength(QTextLength::PercentageLength, 33);
    tableFormat.setColumnWidthConstraints(constraints);

    // fair
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\n\tMediators fair and impartial?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table1 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table1, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table1, 1, 0, "No", &_tableTextFormat);
    TextToCell(table1, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table1, 0, 1, QString::number(_q1Yes), &_tableCellBlue);
    TextToCell(table1, 1, 1, QString::number(_q1No), &_tableCellBlue);
    TextToCell(table1, 2, 1, QString::number(_q1Somewhat), &_tableCellBlue);

    // improved situation
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\tSituation Improved By Mediation?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table2 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table2, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table2, 1, 0, "No", &_tableTextFormat);
    TextToCell(table2, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table2, 0, 1, QString::number(_q2Yes), &_tableCellBlue);
    TextToCell(table2, 1, 1, QString::number(_q2No), &_tableCellBlue);
    TextToCell(table2, 2, 1, QString::number(_q2Somewhat), &_tableCellBlue);

    // helped you communicate
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\tHelped to communicate with other party?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table3 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table3, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table3, 1, 0, "No", &_tableTextFormat);
    TextToCell(table3, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table3, 0, 1, QString::number(_q3Yes), &_tableCellBlue);
    TextToCell(table3, 1, 1, QString::number(_q3No), &_tableCellBlue);
    TextToCell(table3, 2, 1, QString::number(_q3Somewhat), &_tableCellBlue);

    // helped understand other point view
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\tHelped to better understand the issues?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table4 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table4, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table4, 1, 0, "No", &_tableTextFormat);
    TextToCell(table4, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table4, 0, 1, QString::number(_q4Yes), &_tableCellBlue);
    TextToCell(table4, 1, 1, QString::number(_q4No), &_tableCellBlue);
    TextToCell(table4, 2, 1, QString::number(_q4Somewhat), &_tableCellBlue);

    // Would recommend to someone else
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\tRecommend mediation to others?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table5 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table5, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table5, 1, 0, "No", &_tableTextFormat);
    TextToCell(table5, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table5, 0, 1, QString::number(_q5Yes), &_tableCellBlue);
    TextToCell(table5, 1, 1, QString::number(_q5No), &_tableCellBlue);
    TextToCell(table5, 2, 1, QString::number(_q5Somewhat), &_tableCellBlue);

    // was agreement reached
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\tDid you reach an agreement?\n", _headerFormat);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);
    QTextTable *table6 = cursor.insertTable(3, 2, tableFormat);
    TextToCell(table6, 0, 0, "Yes", &_tableTextFormat);
    TextToCell(table6, 1, 0, "No", &_tableTextFormat);
    TextToCell(table6, 2, 0, "Somewhat", &_tableTextFormat);
    TextToCell(table6, 0, 1, QString::number(_q2Yes), &_tableCellBlue);
    TextToCell(table6, 1, 1, QString::number(_q2No), &_tableCellBlue);
    TextToCell(table6, 2, 1, QString::number(_q2Somewhat), &_tableCellBlue);
}

void ResWaReport::AddMPToCasesTable(DisputeTypes disputeType, CourtCaseTypes courtType, bool settled)
{
    CasesTableIndices row;
    // Translate the court type to a table index
    switch(courtType)
    {
    case COURT_T_SMALL_CLAIMS: row = CT_SMALL_CLAIMS; break;
    case COURT_T_JUVENILE: row = CT_JUVENIILE_COURT; break;
    case COURT_T_OTHER: row = CT_OTHER_CASES; break;
    case COURT_T_SUPERIOR: row = CT_SUPERIOR_COURT; break;
    case COURT_T_NONE: row = CT_OTHER_CASES; break;
    }


    // The 1st row is the number of cases, the row+1 is the number settled. 3rd row is percentage
    switch(disputeType)
    {
    case DISPUTE_T_PARENTING_PLAN:
        _casesTable[row][CT_H_PARENTING]++;
        _casesTable[CT_TOTAL_CASES][CT_H_PARENTING]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_PARENTING]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_PARENTING]++;
        }
        break;
    case DISPUTE_T_DIVORCE:
        _casesTable[row][CT_H_DISOLUTION]++;
        _casesTable[CT_TOTAL_CASES][CT_H_DISOLUTION]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_DISOLUTION]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_DISOLUTION]++;
        }
        break;
    case DISPUTE_T_FORECLOSURE:
        _casesTable[row][CT_H_FORECLOSURE]++;
        _casesTable[CT_TOTAL_CASES][CT_H_FORECLOSURE]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_FORECLOSURE]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_FORECLOSURE]++;
        }
        break;
    case DISPUTE_T_TENANT:
    case DISPUTE_T_LANDLORD:
        _casesTable[row][CT_H_TENANT]++;
        _casesTable[CT_TOTAL_CASES][CT_H_TENANT]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_TENANT]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_TENANT]++;
        }
        break;
    case DISPUTE_T_PROPERTY_BUSINESS:
        _casesTable[row][CT_H_BUSINESS]++;
        _casesTable[CT_TOTAL_CASES][CT_H_BUSINESS]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_BUSINESS]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_BUSINESS]++;
        }
        break;
    case DISPUTE_T_WORKPLACE:
        _casesTable[row][CT_H_WORKPLACE]++;
        _casesTable[CT_TOTAL_CASES][CT_H_WORKPLACE]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_WORKPLACE]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_WORKPLACE]++;
        }
        break;
    case DISPUTE_T_NEIGHBORHOOD:
        _casesTable[row][CT_H_NEIGHBOR]++;
        _casesTable[CT_TOTAL_CASES][CT_H_NEIGHBOR]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_NEIGHBOR]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_NEIGHBOR]++;
        }
        break;
    case DISPUTE_T_PARENT_TEEN:
        _casesTable[row][CT_H_PARENT]++;
        _casesTable[CT_TOTAL_CASES][CT_H_PARENT]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_PARENT]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_PARENT]++;
        }
        break;
    default:
        _casesTable[row][CT_H_OTHER]++;
        _casesTable[CT_TOTAL_CASES][CT_H_OTHER]++;
        if(settled)
        {
            _casesTable[row+1][CT_H_OTHER]++;
            _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_OTHER]++;
        }
        break;
    }    
    _casesTable[row][CT_H_TOTAL]++;
    if(settled) _casesTable[row+1][CT_H_TOTAL]++;
    _casesTable[CT_TOTAL_CASES][CT_H_TOTAL]++;
    if(settled) _casesTable[CT_TOTAL_CASES_SETTLED][CT_H_TOTAL]++;
}

void ResWaReport::CalculateCasesTable()
{
    foreach(MediationProcess* mp,  *_processes)
    {
        AddMPToCasesTable(mp->GetDisputeType(), mp->GetCourtType(), mp->IsSettled());
    }

    // Calculate the percentages now that all mp's have been added to the table!
    // (every 3rd row is a percentage calculation based on 2 fields above)

    int row = (int)CT_SMALL_CLAIMS;
    int column = (int)CT_H_PARENTING;

    while (row <= (int)CT_TOTAL_CASES)
    {
        for(column = (int)CT_H_PARENTING; column <= CT_H_TOTAL; ++column)
        {
            if(_casesTable[row][column] != 0)
            {
                // Caution: storing the result of division in an integer causes loss of decimals!!
                double num = _casesTable[row+1][column];
                double denom = _casesTable[row][column];
                double result = num / denom;
                _casesTable[row+2][column] = result * 100;
                //qDebug() << "Calculated percent for [" << row+2 << "][" << column << "] cell:  " << _casesTable[row+1][column] << "/" << _casesTable[row][column] << "= " << _casesTable[row+2][column];
            }
        }
        row = row + 3;
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

// Looks for observers.  Any found are added as training attendees.
// Each session that has any observers adds to the number of trainings conducted.
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
    // The RESWA report calls this one a "Freebie" in that it is copied over to the
    // People section of the report automatically.  So, here, we just copy it too.
    _numByTraining = numTrainings;
}

void ResWaReport::CalculatePeople()
{
    // zero it all out so our numbers are sure to be fresh.
    _numByPhone   //
    = _numChildByPhone //
    = _numByCoaching //
    = _numChildByCoaching //
    = _numByPhoneConcilliation
    = _numChildByPhoneConcilliation
    = _numBySessions
    = _numChildBySessions
    = _numBySessionFacilliation
    = _numChildBySessionFacilliation
    = _numIndirectly
    = _numChildIndirectly
    // _numByTraining   // equals section 4 (TRAINING) total, so we don't want to clear it.
    = _numChildByTraining
    = _numAdditionalServed
    = _numChildAdditionalServed = 0;

    bool isChild = false;  // no children are directly served, so we are just setting this

    foreach(MediationProcess* mp,  *_processes)
    {
        //  For each client in the list of clients... but not for each session
        // check is child... flip a bool if true  (children count in both the child counts and the totals)
        foreach(Party* party, *mp->GetParties())
        {
            // We currently have no mecanism for marking a client as a child, because
            // the DRC does not have any child clients, so, I've added this part just in case
            // a mechanism is added later.  Then one would just have to do that request once here.
            //            if (party is child) {
            //                isChild = true;
            //            }
            //            else {
            //                isChild = false;
            //            }


            // The sum of _numByCoaching and _numByPhone should equal the number of total calls
            // from the CALLS section, assuming a call is only ever one person.

            // PARTS A,B, C, D, and E
            // The sum of _numByPhoneConciliation, _numBySessionFacilitation, and _numBySessions
            // represents all of the people involved in the total number of cases from the
            // CASES section.
            switch(mp->GetSessionType())
            {
            case PHONE_SESSION:
                _numByPhoneConcilliation++;
                if(isChild) {
                    _numChildByPhoneConcilliation++;
                }
                break;
            case FACILITATION_SESSION:
                _numBySessionFacilliation++;
                if(isChild) {
                    _numChildBySessionFacilliation++;
                }
                break;
            case MEDIATION_SESSION:
                _numBySessions++;
                if(isChild) {
                    _numChildBySessions++;
                }
                break;
            case COACHING_SESSION:
                _numByCoaching++;
                if(isChild) {
                    _numChildByCoaching++;
                }
                break;
            default:
                if(mp->GetInfoOnly() || (mp->GetState() == PROCESS_STATE_CLOSED_NO_SESSION))
                {
                    _numByPhone++;
                    if(isChild) {
                        _numChildByPhone++;  // this is likely always 0.
                    }
                }
                break;
            };

            // PART F
            // total number indirectly includes both adults AND children.
            _numIndirectly = _numIndirectly + party->GetPrimary()->getNumberInHousehold();
            _numIndirectly = _numIndirectly + (int)party->GetChildren().size();
            _numChildIndirectly = _numChildIndirectly + (int)party->GetChildren().size();

            // PART G
            // The training number gets copied over when the training section is calculated.

            // PART H
            // Additional people served would be a unique case.  Since we don't have any other fields to check for
            // we will just leave _numAdditionalServed and _numChildAdditionalServed as zero for now.

        }
    }
}
