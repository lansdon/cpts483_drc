#include "partydetailsform.h"
#include "ui_partydetailsform.h"
#include "drc_shared/models/Person.h"

PartyDetailsForm::PartyDetailsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartyDetailsForm)
{
    ui->setupUi(this);
}

PartyDetailsForm::~PartyDetailsForm()
{
    delete ui;
}



void PartyDetailsForm::UpdateLabels()
{
    ui->firstLineEdit->setText(QString::fromStdString(_person.getFirstName()));
}
