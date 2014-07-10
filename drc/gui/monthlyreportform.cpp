#include "monthlyreportform.h"
#include "ui_monthlyreportform.h"

MonthlyReportForm::MonthlyReportForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthlyReportForm)
{
    ui->setupUi(this);
}

MonthlyReportForm::~MonthlyReportForm()
{
    delete ui;
}
