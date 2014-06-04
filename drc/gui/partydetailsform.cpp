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
    ui->middleLineEdit->setText(QString::fromStdString(_person.getMiddleName()));
    ui->lastLineEdit->setText(QString::fromStdString(_person.getLastName()));
    ui->streetLineEdit->setText(QString::fromStdString(_person.getStreet()));
    ui->unitLineEdit->setText(QString::fromStdString(_person.getUnit()));
    ui->cityLineEdit->setText(QString::fromStdString(_person.getCity()));
    ui->stateLineEdit->setText(QString::fromStdString(_person.getState()));
    ui->countyLineEdit->setText(QString::fromStdString(_person.getCounty()));
    ui->zipLineEdit->setText(QString::fromStdString(_person.getZip()));
    ui->emailLineEdit->setText(QString::fromStdString(_person.getEmail()));
    ui->homeLineEdit->setText(QString::fromStdString(_person.getHomePhone()));
    ui->homeExtLineEdit->setText(QString::fromStdString(_person.getHomePhoneExt()));
    ui->workLineEdit->setText(QString::fromStdString(_person.getWorkPhone()));
    ui->workExtLineEdit->setText(QString::fromStdString(_person.getWorkPhoneExt()));
    ui->mobileLineEdit->setText(QString::fromStdString(_person.getMobilePhone()));
    ui->mobileExtLineEdit->setText(QString::fromStdString(_person.getMobilePhoneExt()));
    ui->numInHomeLineEdit->setText(QString::number(_person.getNumberInHousehold()));
    ui->attorneyLineEdit->setText(QString::fromStdString(_person.getAttorney()));
}
