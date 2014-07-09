#include "reswareport.h"
#include "drctypes.h"
#include <QPrinter>
#include <QDesktopServices>
#include <QDebug>
#include <QTextBlock>
#include <QTextTable>


const QString DEF_PDF_PATH = "RES_WA_REPORT.pdf";

ResWaReport::ResWaReport(MediationProcessVector& processes)
    : _processes(processes)
{

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


    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(DEF_PDF_PATH)))
        qDebug() << "Error opening RESWA PDF";

}
///////////////// Report Builder - INTERNAL ///////////////////
// These functions build the different sections of the report
///////////////////////////////////////////////////////////////

void ResWaReport::BuildHeaderSection(QTextCursor& cursor)
{
    cursor.insertText("HEADER!!!!!!!\n\n");

}

void ResWaReport::BuildCasesSection(QTextCursor& cursor)
{
    cursor.insertText("BuildCasesSection\n");

}

void ResWaReport::BuildCallsSection(QTextCursor& cursor)
{
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

    for (auto column = 1; column < columns; ++column) {
        auto cell = table->cellAt(0, column);
        auto cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(QString("drc things %1").arg(column));
    }

    for (auto row = 1; row < rows; ++row) {
        auto cell = table->cellAt(row, 0);
        auto cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(QString("%1").arg(row));

        for (auto column = 1; column < columns; ++column) {
            if ((row-1) % 3 == column-1) {
                cell = table->cellAt(row, column);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.insertText("drc stuff");
            }
        }
    }
}

void ResWaReport::BuildContactsSection(QTextCursor& cursor)
{
    cursor.insertText("\n\nBuildContactsSection\n\n");

}

void ResWaReport::BuildTrainingSection(QTextCursor& cursor)
{
    cursor.insertText("BuildTrainingSection\n\n");

}

void ResWaReport::BuildPeopleServedSection(QTextCursor& cursor)
{
    cursor.insertText("BuildPeopleServedSection\n\n");

}

void ResWaReport::BuildOutreachSection(QTextCursor& cursor)
{
    cursor.insertText("BuildOutreachSection\n\n");

}

void ResWaReport::BuildStaffSection(QTextCursor& cursor)
{
    cursor.insertText("BuildStaffSection\n\n");

}

void ResWaReport::BuildEvaluationSection(QTextCursor& cursor)
{
    cursor.insertText("BuildEvaluationSection\n\n");

}
