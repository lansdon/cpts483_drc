#include "persondetailsform.h"
#include "ui_persondetailsform.h"
#include "Person.h"
#include <QDebug>

PersonDetailsForm::PersonDetailsForm(QWidget *parent, Person* person, bool bPopup)
    : QWidget(parent)
    , ui(new Ui::PersonDetailsForm)
    , _person(person ? person : new Person())
    , _shouldCleanPersonPointer(person == nullptr)
    , _bPopup(bPopup)
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
    ui->firstLineEdit->setText((_person->getFirstName()));
    ui->middleLineEdit->setText((_person->getMiddleName()));
    ui->lastLineEdit->setText((_person->getLastName()));
    ui->streetLineEdit->setText((_person->getStreet()));
    ui->unitLineEdit->setText((_person->getUnit()));
    ui->cityLineEdit->setText((_person->getCity()));
    ui->stateLineEdit->setText((_person->getState()));
    ui->countyLineEdit->setText((_person->getCounty()));
    ui->zipLineEdit->setText((_person->getZip()));
    ui->emailLineEdit->setText((_person->getEmail()));
    ui->homeLineEdit->setText((_person->getPrimaryPhone()));
    ui->homeExtLineEdit->setText((_person->getPrimaryPhoneExt()));
    ui->workLineEdit->setText((_person->getSecondaryPhone()));
    ui->workExtLineEdit->setText((_person->getSecondaryPhoneExt()));
//    ui->mobileLineEdit->setText((_person->getMobilePhone()));
//    ui->mobileExtLineEdit->setText((_person->getMobilePhoneExt()));
    ui->numInHomeLineEdit->setText(QString::number(_person->getNumberInHousehold()));
    ui->attorneyLineEdit->setText((_person->getAttorney()));

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

    _person->setFirstName(ui->firstLineEdit->text());
    _person->setMiddleName(ui->middleLineEdit->text());
    _person->setLastName(ui->lastLineEdit->text());
    _person->setStreet(ui->streetLineEdit->text());
    _person->setUnit(ui->unitLineEdit->text());
    _person->setCity(ui->cityLineEdit->text());
    _person->setState(ui->stateLineEdit->text());
    _person->setCounty(ui->countyLineEdit->text());
    _person->setZip(ui->zipLineEdit->text());
    _person->setEmail(ui->emailLineEdit->text());
    _person->setPrimaryPhone(ui->homeLineEdit->text());
    _person->setPrimaryPhoneExt(ui->homeExtLineEdit->text());
    _person->setSecondaryPhone(ui->workLineEdit->text());
    _person->setSecondaryPhoneExt(ui->workExtLineEdit->text());
//    _person->setMobilePhone(ui->mobileLineEdit->text());
//    _person->setMobilePhoneExt(ui->mobileExtLineEdit->text());
    _person->setNumberInHousehold(ui->numInHomeLineEdit->text().toInt());
    _person->setAttorney(ui->attorneyLineEdit->text());

    //emit PersonSaved(_person);
    //emit SaveSignaled();
    Mediator::Call(MKEY_GUI_MP_SHOULD_UPDATE);
    if(_bPopup)
    {
        this->close();
    }
}

void PersonDetailsForm::on_editButton_clicked()
{
    SetEditMode(true);
}

void PersonDetailsForm::on_deleteButton_clicked()
{
    emit PersonDeleted(_person);

    SetEditMode(true);
    _person = new Person();
    UpdateLabels();

    if(_bPopup)
    {
        this->close();
    }
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
//    if(_shouldCleanPersonPointer)
//        delete _person;
//    _shouldCleanPersonPointer = false;
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
