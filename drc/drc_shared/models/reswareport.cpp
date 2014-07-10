#include "reswareport.h"
#include "drctypes.h"
#include <QPrinter>
#include <QDesktopServices>
#include <QDebug>
#include <QTextBlock>
#include <QTextTable>
#include <QTextEdit>
#include <QDate>


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
    , _q1No(0)
    , _q1Yes(0)
    , _q1Somewhat(0)
    , _q2No(0)
    , _q2Yes(0)
    , _q2Somewhat(0)
    , _q3No(0)
    , _q3Yes(0)
    , _q3Somewhat(0)
    , _q4No(0)
    , _q4Yes(0)
    , _q4Somewhat(0)
    , _q5No(0)
    , _q5Yes(0)
    , _q5Somewhat(0)
    , _q6No(0)
    , _q6Yes(0)
    , _q6Somewhat(0)
{

    _headerFormat.setFontPointSize(12);
    _tableTextFormat.setFontPointSize(8);
    _tableCellBlue.setBackground(QColor("#3010ee"));
    _tableIndexDark.setBackground(QColor("#e0e0e0"));
    _tableIndexLight.setBackground(QColor("#eeeee0"));

    // Init table matrix with zeros.
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
    constraints << QTextLength(QTextLength::PercentageLength, 35);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(CasesTableRows, CasesTableCols, tableFormat);
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

    for (auto row = 1; row < CasesTableRows; ++row)
    {
        for (auto column = 1; column < CasesTableCols; ++column)
        {
            QTextTableCell cell = table->cellAt(row, column);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText(QString::number(_casesTable[row][column]));
        }
    }

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
    int rows = 2, cols = 7;

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n3) Contacts (proactive outreach events\n", _headerFormat);
    cursor.insertText("!! This information is not available !!\n", _headerFormat);

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    constraints << QTextLength(QTextLength::PercentageLength, 10);
    constraints << QTextLength(QTextLength::PercentageLength, 10);
    constraints << QTextLength(QTextLength::PercentageLength, 10);
    constraints << QTextLength(QTextLength::PercentageLength, 10);
    constraints << QTextLength(QTextLength::PercentageLength, 10);
    constraints << QTextLength(QTextLength::PercentageLength, 10);

    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(rows, cols, tableFormat);
    // HEADERS
    TextToCell(table, 0, 1, "Presentation", &_tableTextFormat);
    TextToCell(table, 0, 2, "TV", &_tableTextFormat);
    TextToCell(table, 0, 3, "Radio", &_tableTextFormat);
    TextToCell(table, 0, 4, "Newspaper", &_tableTextFormat);
    TextToCell(table, 0, 5, "other", &_tableTextFormat);
    TextToCell(table, 0, 6, "Press Releases", &_tableTextFormat);
    // ROW INDICES
    TextToCell(table, 1, 0, "Total Contacts", &_tableTextFormat);

    // VALUES


}

void ResWaReport::BuildTrainingSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n4) TRAINING & IN-SERVICES\n");

    // TABLE STUFFS
    int rows = 3, cols = 15;

    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 15);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    constraints << QTextLength(QTextLength::PercentageLength, 5);
    tableFormat.setColumnWidthConstraints(constraints);
    QTextTable *table = cursor.insertTable(rows, cols, tableFormat);
    // HEADERS
    TextToCell(table, 0, 1, "40 Hour Basic", &_tableTextFormat);
    TextToCell(table, 0, 2, "Family Parenting Training", &_tableTextFormat);
    TextToCell(table, 0, 3, "Family Med", &_tableTextFormat);
    TextToCell(table, 0, 4, "Conflict Resolution Skillz", &_tableTextFormat);
    TextToCell(table, 0, 5, "Peer Mediation", &_tableTextFormat);
    TextToCell(table, 0, 6, "Other youth training", &_tableTextFormat);
    TextToCell(table, 0, 7, "Parent Teen", &_tableTextFormat);
    TextToCell(table, 0, 8, "Victim Offender", &_tableTextFormat);
    TextToCell(table, 0, 9, "Group Facillitation", &_tableTextFormat);
    TextToCell(table, 0, 10, "Phone Conilliation", &_tableTextFormat);
    TextToCell(table, 0, 11, "Workplace", &_tableTextFormat);
    TextToCell(table, 0, 12, "In-service", &_tableTextFormat);
    TextToCell(table, 0, 13, "Other", &_tableTextFormat);
    TextToCell(table, 0, 14, "Total", &_tableTextFormat);
    // ROW INDICES
    TextToCell(table, 1, 0, "# of training and in-services conducted", &_tableTextFormat);
    TextToCell(table, 2, 0, "# of persons attending trainings and in-services", &_tableTextFormat);

    // VALUES


}

void ResWaReport::BuildPeopleServedSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n5) People Served\n", _headerFormat);

}

void ResWaReport::BuildOutreachSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n6) Outreach \n", _headerFormat);

}

void ResWaReport::BuildStaffSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n7) BuildStaffSection\n", _headerFormat);

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
