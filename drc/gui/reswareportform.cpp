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
#include "reportrequest.h"

const QString DEF_PDF_PATH = "RES_WA_REPORT.pdf";

ResWaReportForm::ResWaReportForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResWaReportForm)

{
    ui->setupUi(this);

    ui->frame->setStyleSheet("QFrame#frame {\
                                               border: 2px solid gray;\
                                               border-radius: 5px;\
                                               margin-top: 1.3em;\
                                              }");

    ui->reswaLogoLabel->setPixmap(QPixmap(":images/reswalogo.gif"));

}

ResWaReportForm::~ResWaReportForm()
{
    delete ui;
}

// Mediator Callback when report comes from DB.
void RecieveReport(MediatorArg arg)
{
    if(arg.IsSuccessful())
    {
//        auto report = arg.getArg<ResWaReport>();
//        if(report)
//        {
//            BuildReport();
//        }
    }
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

}



void ResWaReportForm::on_showResportBtn_clicked()
{
    // Query parameters
    bool firstHalfOfYear = (bool)ui->yearHalfComboBox->currentIndex();
    ReportRequest* params = new ReportRequest(
                firstHalfOfYear ? 1 : 7, // set month anywhere in range
                ui->yearSpinBox->value()
                );

    Mediator::Call(MKEY_GUI_REQUEST_RESWA_REPORT, params);

    // Temporarily displaying test data... this has to move to
    // the response when report object arrives.
    BuildReport();
}

void ResWaReportForm::on_cancelBtn_clicked()
{
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}
