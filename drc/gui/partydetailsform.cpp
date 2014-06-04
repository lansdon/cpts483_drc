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

void PartyDetailsForm::on_emailLineEdit_textChanged(const QString &arg1)
{
    // integers 1 to 9999
    QRegExp rx("[1-9]\\d{0,3}");
    // the validator treats the regexp as "^[1-9]\\d{0,3}$"
    QRegExpValidator v(rx, 0);
    QString s;
    int pos = 0;

    s = "0";     v.validate(s, pos);    // returns Invalid
    s = "12345"; v.validate(s, pos);    // returns Invalid
    s = "1";     v.validate(s, pos);    // returns Acceptable
}
