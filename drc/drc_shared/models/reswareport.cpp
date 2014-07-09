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

ResWaReport::ResWaReport(MediationProcessVector *processes)
    : _processes(processes)
{

    _headerFormat.setFontPointSize(12);
    _tableTextFormat.setFontPointSize(8);

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
    tableFormat.setBackground(QColor("#e0e0e0"));
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
    int rows = 19, columns = 14;
    QTextTable *table = cursor.insertTable(rows, columns, tableFormat);
    TextToCell(table, 1, 0, "Small claims court cases");
    TextToCell(table, 2, 0, "Small Claims Court cases settled");
    TextToCell(table, 3, 0, "Percentage of Small Claims cases settled");
    TextToCell(table, 4, 0, "Other District Cout cases");
    TextToCell(table, 5, 0, "Other District Cout cases settled");
    TextToCell(table, 6, 0, "Percentage of district court cases settled");
    TextToCell(table, 7, 0, "Juvenile Court cases");
    TextToCell(table, 8, 0, "Percentage of Juvenile cases settled");
    TextToCell(table, 9, 0, "Superior Court cases");
    TextToCell(table, 10, 0, "Superior Court cases settled");
    TextToCell(table, 11, 0, "Percentage of Superior cases settled");
    TextToCell(table, 12, 0, "Other cases");
    TextToCell(table, 13, 0, "Other cases settled");
    TextToCell(table, 14, 0, "Percentage of Other cases settled");
    TextToCell(table, 15, 0, "Total cases");
    TextToCell(table, 16, 0, "Cases Settled");
    TextToCell(table, 17, 0, "Small claims court cases");
    TextToCell(table, 18, 0, "Percentage of total cases settled");
    TextToCell(table, 0, 1, "Parenting Plans");
    TextToCell(table, 0, 2, "Disolution");
    TextToCell(table, 0, 3, "Foreclosure");
    TextToCell(table, 0, 4, "Tenant Landlord");
    TextToCell(table, 0, 5, "Business");
    TextToCell(table, 0, 6, "Workplace");
    TextToCell(table, 0, 7, "Neighbor");
    TextToCell(table, 0, 8, "Victim Offender");
    TextToCell(table, 0, 9, "Parent Teen");
    TextToCell(table, 0, 10, "School");
    TextToCell(table, 0, 11, "Elder");
    TextToCell(table, 0, 12, "Other");
    TextToCell(table, 0, 13, "Total");
}

void ResWaReport::TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* format)
{
    if(!format) format = &_tableTextFormat;

    auto cell = table->cellAt(row, col);
    auto cellCursor = cell.firstCursorPosition();
    cellCursor.insertText(txt, *format);
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
