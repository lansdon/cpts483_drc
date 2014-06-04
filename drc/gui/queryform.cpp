#include "queryform.h"
#include "ui_queryform.h"

QueryForm::QueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryForm)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new PartyDetailsForm(),"Party");
}

QueryForm::~QueryForm()
{
    delete ui;
}
