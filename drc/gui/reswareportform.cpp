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
#include "reswareport.h"

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

    Mediator::Register(MKEY_DB_REQUEST_RESWA_REPORT_DONE, [this](MediatorArg arg){RecieveReport(arg);});

}

ResWaReportForm::~ResWaReportForm()
{
    delete ui;
}

// Mediator Callback when report comes from DB.
void ResWaReportForm::RecieveReport(MediatorArg arg)
{
    if(arg.IsSuccessful())
    {
        auto report = arg.getArg<ResWaReport*>();
        if(report)
        {
            report->BuildReport();
        }
    }
}


void ResWaReportForm::BuildReport()
{


}



void ResWaReportForm::on_showResportBtn_clicked()
{
    // Query parameters
    bool firstHalfOfYear = (bool)ui->yearHalfComboBox->currentIndex();
    ReportRequest* params = new ReportRequest(
                firstHalfOfYear ? 7 : 1, // set month anywhere in range
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
