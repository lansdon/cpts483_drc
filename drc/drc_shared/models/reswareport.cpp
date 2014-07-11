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

//    cursor.insertText("Total calls: " + QString::number(_totalCalls) + "\n\n");

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
    TextToCell(table, 0, 0, "# of trainings", &_tableTextFormat);
    TextToCell(table, 0, 1, "# attending trainings", &_tableTextFormat);
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
    TextToCell(table, 0, 0, "Cases Settled", &_tableTextFormat);
    TextToCell(table, 1, 0, "Percentage of total cases settled", &_tableTextFormat);
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
    TextToCell(tableB, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableB, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableC, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableC, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableD, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableD, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableE, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableE, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableF, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableF, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableG, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableG, 1, 0, "Children Served", &_tableTextFormat);
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
    TextToCell(tableH, 0, 0, "All people Served", &_tableTextFormat);
    TextToCell(tableH, 1, 0, "Children Served", &_tableTextFormat);
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
    cursor.insertText("\tMediators fair and impartial?\n", _headerFormat);
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q1Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q1No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q1Somewhat) + "\n"));
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
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q2Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q2No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q2Somewhat) + "\n"));
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
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q3Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q3No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q3Somewhat) + "\n"));
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
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q4Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q4No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q4Somewhat) + "\n"));
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
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q5Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q5No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q5Somewhat) + "\n"));
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
//    cursor.insertText(QString("\t\t\tYes: " + QString::number(_q6Yes) + "\n"));
//    cursor.insertText(QString("\t\t\tNo: " + QString::number(_q6No) + "\n"));
//    cursor.insertText(QString("\t\t\tSomewhat: " + QString::number(_q6Somewhat) + "\n"));
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
