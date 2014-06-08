#include "persondetailsform.h"
#include "ui_persondetailsform.h"
#include "Person.h"
#include <QDebug>

PersonDetailsForm::PersonDetailsForm(QWidget *parent, Person* person)
    : QWidget(parent)
    , ui(new Ui::PersonDetailsForm)
    , _person(person ? person : new Person())
    , _shouldCleanPersonPointer(person == nullptr)
{
    ui->setupUi(this);

    // Setup Validations
    ui->zipLineEdit->setValidator(new QIntValidator(ui->zipLineEdit));
    ui->numInHomeLineEdit->setValidator(new QIntValidator(ui->numInHomeLineEdit));

    // If a valid person object was passed, display it and don't go into edit mode.
    if(person)
        UpdateLabels();
    else
        SetEditMode(true);      // Blank record, start in edit mode.

}

PersonDetailsForm::~PersonDetailsForm()
{
    delete ui;
    cleanPerson();
}



void PersonDetailsForm::UpdateLabels()
{
    ui->firstLineEdit->setText(QString::fromStdString(_person->getFirstName()));
    ui->middleLineEdit->setText(QString::fromStdString(_person->getMiddleName()));
    ui->lastLineEdit->setText(QString::fromStdString(_person->getLastName()));
    ui->streetLineEdit->setText(QString::fromStdString(_person->getStreet()));
    ui->unitLineEdit->setText(QString::fromStdString(_person->getUnit()));
    ui->cityLineEdit->setText(QString::fromStdString(_person->getCity()));
    ui->stateLineEdit->setText(QString::fromStdString(_person->getState()));
    ui->countyLineEdit->setText(QString::fromStdString(_person->getCounty()));
    ui->zipLineEdit->setText(QString::fromStdString(_person->getZip()));
    ui->emailLineEdit->setText(QString::fromStdString(_person->getEmail()));
    ui->homeLineEdit->setText(QString::fromStdString(_person->getHomePhone()));
    ui->homeExtLineEdit->setText(QString::fromStdString(_person->getHomePhoneExt()));
    ui->workLineEdit->setText(QString::fromStdString(_person->getWorkPhone()));
    ui->workExtLineEdit->setText(QString::fromStdString(_person->getWorkPhoneExt()));
    ui->mobileLineEdit->setText(QString::fromStdString(_person->getMobilePhone()));
    ui->mobileExtLineEdit->setText(QString::fromStdString(_person->getMobilePhoneExt()));
    ui->numInHomeLineEdit->setText(QString::number(_person->getNumberInHousehold()));
    ui->attorneyLineEdit->setText(QString::fromStdString(_person->getAttorney()));

    SetEditMode(false);
}

void PersonDetailsForm::SetWidgetInvalid(QWidget *widget)
{
    QPalette palette;
    palette.setColor( widget->foregroundRole(), Qt::red );
    widget->setPalette(palette);
}

void PersonDetailsForm::SetWidgetValid(QWidget *widget)
{
    QPalette palette;
    palette.setColor( widget->foregroundRole(), Qt::black );
    widget->setPalette(palette);
}

bool PersonDetailsForm::ValidateForm()
{
    // Check every field and return true if they all pass, else false.

    if(
        ProcessPhoneNumber(ui->homeLineEdit->text(), ui->homeLineEdit)
        &&
        ProcessPhoneNumber(ui->workLineEdit->text(), ui->workLineEdit)
        &&
        ProcessPhoneNumber(ui->mobileLineEdit->text(), ui->mobileLineEdit)
        &&
        ProcessEmail(ui->emailLineEdit->text(), ui->emailLineEdit)
    )
    {
        return true;
    }

    return false;
}

void PersonDetailsForm::on_emailLineEdit_textChanged(const QString &arg1)
{
   ProcessEmail(arg1, ui->emailLineEdit);
}

bool PersonDetailsForm::ProcessEmail(const QString& string, QLineEdit* widget)
{
    // email validation - <something>@<something>.<two to three letters>
    QRegExp rx("(^.*@.*[.][a-z]{2,3})");
    QRegExpValidator v(rx, 0);
    QString s = string;
    if(!rx.exactMatch(s))
    {
        SetWidgetInvalid(widget);
        return false;
    } else {
        SetWidgetValid(widget);
        return true;
    }
}

bool PersonDetailsForm::ProcessPhoneNumber(const QString& string, QLineEdit* widget)
{
    if(string.length() == 0) return true;

    QString s = string;

    // Auto complete first dash
    QRegExp rx("(^[0-9]{3})");
    if(rx.exactMatch(s))
        s.append("-");

    // Auto complete second dash
    rx.setPattern("^[0-9]{3}-[0-9]{3}");
    if(rx.exactMatch(s))
        s.append("-");

    // phone validation - xxx-xxx-xxxx
    rx.setPattern("^[0-9]{3}-[0-9]{3}-[0-9]{4}");
    widget->setText(s);
    if(!rx.exactMatch(s))
    {
        SetWidgetInvalid(widget);
        return false;
    } else {
        SetWidgetValid(widget);
        return true;
    }
}

void PersonDetailsForm::on_workLineEdit_textChanged(const QString &arg1)
{
    ProcessPhoneNumber(arg1, ui->workLineEdit);
}

void PersonDetailsForm::on_homeLineEdit_textChanged(const QString &arg1)
{
    ProcessPhoneNumber(arg1, ui->homeLineEdit);
}

void PersonDetailsForm::on_mobileLineEdit_textChanged(const QString &arg1)
{
    ProcessPhoneNumber(arg1, ui->mobileLineEdit);
}

void PersonDetailsForm::on_saveButton_clicked()
{
    SetEditMode(false);

    _person->setFirstName(ui->firstLineEdit->text().toStdString());
    _person->setMiddleName(ui->middleLineEdit->text().toStdString());
    _person->setLastName(ui->lastLineEdit->text().toStdString());
    _person->setStreet(ui->streetLineEdit->text().toStdString());
    _person->setUnit(ui->unitLineEdit->text().toStdString());
    _person->setCity(ui->cityLineEdit->text().toStdString());
    _person->setState(ui->stateLineEdit->text().toStdString());
    _person->setCounty(ui->countyLineEdit->text().toStdString());
    _person->setZip(ui->zipLineEdit->text().toStdString());
    _person->setEmail(ui->emailLineEdit->text().toStdString());
    _person->setHomePhone(ui->homeLineEdit->text().toStdString());
    _person->setHomePhoneExt(ui->homeExtLineEdit->text().toStdString());
    _person->setWorkPhone(ui->workLineEdit->text().toStdString());
    _person->setWorkPhoneExt(ui->workExtLineEdit->text().toStdString());
    _person->setMobilePhone(ui->mobileLineEdit->text().toStdString());
    _person->setMobilePhoneExt(ui->mobileExtLineEdit->text().toStdString());
    _person->setNumberInHousehold(ui->numInHomeLineEdit->text().toInt());
    _person->setAttorney(ui->attorneyLineEdit->text().toStdString());

    // To do - Send Save Party signal

}

void PersonDetailsForm::on_editButton_clicked()
{
    SetEditMode(true);
}

void PersonDetailsForm::on_deleteButton_clicked()
{
    SetEditMode(true);
    _person = new Person();
    UpdateLabels();

    // To do, send Delete Party signal
}

void PersonDetailsForm::SetEditMode(bool editModeOn)
{
    ui->firstLineEdit->setEnabled(editModeOn);
    ui->middleLineEdit->setEnabled(editModeOn);
    ui->lastLineEdit->setEnabled(editModeOn);
    ui->streetLineEdit->setEnabled(editModeOn);
    ui->unitLineEdit->setEnabled(editModeOn);
    ui->cityLineEdit->setEnabled(editModeOn);
    ui->stateLineEdit->setEnabled(editModeOn);
    ui->countyLineEdit->setEnabled(editModeOn);
    ui->zipLineEdit->setEnabled(editModeOn);
    ui->emailLineEdit->setEnabled(editModeOn);
    ui->homeLineEdit->setEnabled(editModeOn);
    ui->homeExtLineEdit->setEnabled(editModeOn);
    ui->workLineEdit->setEnabled(editModeOn);
    ui->workExtLineEdit->setEnabled(editModeOn);
    ui->mobileLineEdit->setEnabled(editModeOn);
    ui->mobileExtLineEdit->setEnabled(editModeOn);
    ui->numInHomeLineEdit->setEnabled(editModeOn);
    ui->attorneyLineEdit->setEnabled(editModeOn);

    ui->saveButton->setEnabled(editModeOn);
    ui->editButton->setEnabled(!editModeOn);

    _editModeOn = editModeOn;

}

void PersonDetailsForm::cleanPerson()
{
    if(_shouldCleanPersonPointer)
        delete _person;
    _shouldCleanPersonPointer = false;
}

void PersonDetailsForm::on_firstLineEdit_returnPressed()
{

}

void PersonDetailsForm::SetPerson(Person *p)
{
    cleanPerson();
    _person = p;
    UpdateLabels();
}
