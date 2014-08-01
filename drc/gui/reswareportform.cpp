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
#include <QMessageBox>>

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

    ui->countyComboBox->setItemText(COUNTY_NONE, StringForCountyIds(COUNTY_NONE));
    ui->countyComboBox->setItemText(COUNTY_BENTON, StringForCountyIds(COUNTY_BENTON));
    ui->countyComboBox->setItemText(COUNTY_FRANLKIN, StringForCountyIds(COUNTY_FRANLKIN));
    ui->countyComboBox->setItemText(COUNTY_GRANT, StringForCountyIds(COUNTY_GRANT));
    ui->countyComboBox->setItemText(COUNTY_ADAMS, StringForCountyIds(COUNTY_ADAMS));
    ui->countyComboBox->setItemText(COUNTY_WALLAWALLA, StringForCountyIds((COUNTY_WALLAWALLA)));
    ui->countyComboBox->setItemText(COUNTY_OTHER, StringForCountyIds(COUNTY_OTHER));

    _unregMediatorReportDoneCall = Mediator::Register(MKEY_DB_REQUEST_RESWA_REPORT_DONE, [this](MediatorArg arg){RecieveReport(arg);});

}

ResWaReportForm::~ResWaReportForm()
{
    delete ui;
    Mediator::Unregister(MKEY_DB_REQUEST_RESWA_REPORT_DONE, _unregMediatorReportDoneCall);
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


void ResWaReportForm::on_showResportBtn_clicked()
{
    // Require County!
    if(ui->countyComboBox->currentIndex() == COUNTY_NONE)
    {
        QMessageBox msgBox;
        msgBox.setText("You must select a county.");
        msgBox.exec();
    }
    else
    {
        // Query parameters
        bool firstHalfOfYear = (bool)ui->yearHalfComboBox->currentIndex();
        ReportRequest* params = new ReportRequest(
                                                firstHalfOfYear ? 7 : 1, // set month anywhere in range
                                                ui->yearSpinBox->value(),
                                                (CountyIds)ui->countyComboBox->currentIndex()
                                                );

        Mediator::Call(MKEY_GUI_REQUEST_RESWA_REPORT, params);
        Mediator::Call(MKEY_GUI_ENABLE_MENUS);
    }
}

void ResWaReportForm::on_cancelBtn_clicked()
{
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}
