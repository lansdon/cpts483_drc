#include "monthlyreportform.h"
#include "ui_monthlyreportform.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "drctypes.h"
#include "reportrequest.h"

#include <QMessageBox>

MonthlyReportForm::MonthlyReportForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthlyReportForm)
{
    ui->setupUi(this);

    ui->frame->setStyleSheet("QFrame#frame {\
                                               border: 2px solid gray;\
                                               border-radius: 5px;\
                                               margin-top: 1.3em;\
                                              }");

    ui->logoLabel->setPixmap(QPixmap(":images/drclogo.png"));

    ui->countyComboBox->setItemText(COUNTY_NONE, StringForCountyIds(COUNTY_NONE));
    ui->countyComboBox->setItemText(COUNTY_BENTON, StringForCountyIds(COUNTY_BENTON));
    ui->countyComboBox->setItemText(COUNTY_FRANLKIN, StringForCountyIds(COUNTY_FRANLKIN));
    ui->countyComboBox->setItemText(COUNTY_GRANT, StringForCountyIds(COUNTY_GRANT));
    ui->countyComboBox->setItemText(COUNTY_ADAMS, StringForCountyIds(COUNTY_ADAMS));
    ui->countyComboBox->setItemText(COUNTY_WALLAWALLA, StringForCountyIds((COUNTY_WALLAWALLA)));
    ui->countyComboBox->setItemText(COUNTY_OTHER, StringForCountyIds(COUNTY_OTHER));

    Mediator::Register(MKEY_DB_REQUEST_MONTHLY_REPORT_DONE, [this](MediatorArg arg){RecieveReport(arg);});
}

MonthlyReportForm::~MonthlyReportForm()
{
    delete ui;
}

// Mediator Callback when report comes from DB.
void MonthlyReportForm::RecieveReport(MediatorArg arg)
{
    if(arg.IsSuccessful())
    {
        // TO DO - CHANGE THIS TO MONTLY REPORT!!!
        auto report = arg.getArg<monthlyreport*>();
        if(report)
        {
            report->pdfReport();
        }
    }
}

void MonthlyReportForm::on_showResportBtn_clicked()
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
        ReportRequest* params = new ReportRequest(
                                                ui->monthComboBox->currentIndex() + 1, // add 1 because of 0 index combobox
                                                ui->yearSpinBox->value(),
                                                (CountyIds)ui->countyComboBox->currentIndex()
                                                );

        Mediator::Call(MKEY_GUI_REQUEST_MONTHLY_REPORT, params);

    }
}

void MonthlyReportForm::on_cancelBtn_clicked()
{
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}
