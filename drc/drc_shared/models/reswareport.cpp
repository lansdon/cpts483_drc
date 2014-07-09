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
//    tableFormat.setBackground(QColor("#e0e0e0"));
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



void ResWaReport::BuildCallsSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\n");
    QTextTableFormat tableFormat;
    tableFormat.setBackground(QColor("#e0e0e0"));
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 16);
    constraints << QTextLength(QTextLength::PercentageLength, 28);
    constraints << QTextLength(QTextLength::PercentageLength, 28);
    constraints << QTextLength(QTextLength::PercentageLength, 28);
    tableFormat.setColumnWidthConstraints(constraints);
    int rows = 5, columns = 5;
    QTextTable *table = cursor.insertTable(rows, columns, tableFormat);
    TextToCell(table, 0, 0, "wer");
//    for (auto column = 1; column < columns; ++column) {
//        auto cell = table->cellAt(0, column);
//        auto cellCursor = cell.firstCursorPosition();
//        cellCursor.insertText(QString("drc things %1").arg(column));
//    }

//    for (auto row = 1; row < rows; ++row) {
//        auto cell = table->cellAt(row, 0);
//        auto cellCursor = cell.firstCursorPosition();
//        cellCursor.insertText(QString("%1").arg(row));

//        for (auto column = 1; column < columns; ++column) {
//            if ((row-1) % 3 == column-1) {
//                cell = table->cellAt(row, column);
//                QTextCursor cellCursor = cell.firstCursorPosition();
//                cellCursor.insertText("drc stuff");
//            }
//        }
//    }
}

void ResWaReport::BuildContactsSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\n\nBuildContactsSection\n\n");
//    QTextTableFormat tableFormat;
//    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
//    tableFormat.setCellPadding(1);
//    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 40));
//    tableFormat.setAlignment(Qt::AlignLeft);
//    cursor.insertTable(4, 2, tableFormat);

}

void ResWaReport::BuildTrainingSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("BuildTrainingSection\n\n");

}

void ResWaReport::BuildPeopleServedSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("BuildPeopleServedSection\n\n");

}

void ResWaReport::BuildOutreachSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("BuildOutreachSection\n\n");

}

void ResWaReport::BuildStaffSection(QTextCursor& cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("BuildStaffSection\n\n");

}

void ResWaReport::BuildEvaluationSection(QTextCursor& cursor)
{
    cursor.insertBlock();
    cursor.insertText("BuildEvaluationSection\n\n");

    cursor.movePosition(QTextCursor::End);

    QTextCharFormat format(cursor.charFormat());
    format.setFontFamily("Courier");

    QTextCharFormat boldFormat = format;
    boldFormat.setFontWeight(QFont::Bold);

    cursor.insertBlock();
    cursor.insertText(" ", boldFormat);

    QDate date = QDate::currentDate();
    int year = date.year(), month = date.month();

    for (int weekDay = 1; weekDay <= 7; ++weekDay) {
     cursor.insertText(QString("%1 ").arg(QDate::shortDayName(weekDay), 3),
         boldFormat);
    }

    cursor.insertBlock();
    cursor.insertText(" ", format);

    for (int column = 1; column < QDate(year, month, 1).dayOfWeek(); ++column) {
     cursor.insertText("    ", format);
    }

    for (int day = 1; day <= date.daysInMonth(); ++day) {
     int weekDay = QDate(year, month, day).dayOfWeek();

     if (QDate(year, month, day) == date)
         cursor.insertText(QString("%1 ").arg(day, 3), boldFormat);
     else
         cursor.insertText(QString("%1 ").arg(day, 3), format);

     if (weekDay == 7) {
         cursor.insertBlock();
         cursor.insertText(" ", format);
     }
    }
}
