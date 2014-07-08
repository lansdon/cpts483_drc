#include "reswareportform.h"
#include "ui_reswareportform.h"
#include <QTextDocument>
#include <QTextTableFormat>
#include <QGridLayout>
#include <QTextCursor>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QPrinter>
#include <QTextBlock>
#include <QTextTable>
#include <QDesktopServices>
#include <QDebug>
#include "Mediator.h"
#include "MediatorKeys.h"

const QString DEF_PDF_PATH = "RES_WA_REPORT.pdf";

ResWaReportForm::ResWaReportForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResWaReportForm)
{
    ui->setupUi(this);

    BuildReport();
}

ResWaReportForm::~ResWaReportForm()
{
    delete ui;
}

void ResWaReportForm::BuildReport()
{
    _report = new QTextDocument();
    _report->begin();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(DEF_PDF_PATH);


    QTextCursor cursor(_report);
    cursor.insertText("Text and stuff");
    cursor.insertText("Text and stuff");
    cursor.insertText("Text and stuff");
    cursor.insertText("Text and stuff");
    cursor.insertText("Text and stuff");


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
        cellCursor.insertText(tr("Team %1").arg(column));
    }

    for (auto row = 1; row < rows; ++row) {
        auto cell = table->cellAt(row, 0);
        auto cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(tr("%1").arg(row));

        for (auto column = 1; column < columns; ++column) {
            if ((row-1) % 3 == column-1) {
                cell = table->cellAt(row, column);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.insertText(tr("On duty"));
            }
        }
    }


    _report->end();

    _report->print(&printer);


    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(DEF_PDF_PATH)))
        qDebug() << "Error opening RESWA PDF";

    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}
