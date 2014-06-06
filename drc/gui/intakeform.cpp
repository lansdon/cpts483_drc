#include "intakeform.h"
#include "ui_intakeform.h"

// Qt
#include <QDebug>

// DRC
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/models/DRCModels.h"

IntakeForm::IntakeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntakeForm)
{
    ui->setupUi(this);

    //mainParty = new PartyDetailsForm();
    //partys.push_back(new PartyDetailsForm());
    //ui->mainPartyTabWidget->addTab(partys[0],"Party 1");
    //update();
    initPartys();
//    _currentIntake.addClaimant(Person(""));


//    initPartys();
//    ui->OtherPartyTabWidget->clear();
//    for(uint i =0; i< partys.size();i++)
//    {
//        ui->OtherPartyTabWidget->addTab(partys[i], QString::fromStdString("Party " + std::to_string((ui->OtherPartyTabWidget->count())+2)));
//        _currentIntake.addRespondents(Person(""));
//    }

    // One time setup of async handlers.
    _asyncLoadIntake = new AsyncMediatorCall(MKEY_GUI_LOAD_INTAKE_FORM, MKEY_DB_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){ Recieve_LoadIntakeForm(arg); }, nullptr, true);
    _asyncSaveIntake = new AsyncMediatorCall(MKEY_GUI_SUBMIT_INTAKE_FORM, MKEY_DB_PERSIST_INTAKE_FORM_DONE, [this](MediatorArg arg){ Recieve_SaveIntakeForm(arg); }, nullptr, true);

}

IntakeForm::~IntakeForm()
{
    delete ui;
}

void IntakeForm::on_saveButton_clicked()
{
    // SAVE
    qDebug() << "Gui -> SAVE INTAKE FORM PRESSED";
    _asyncSaveIntake->GetMediatorArg().SetArg(&_currentIntake);
    _asyncSaveIntake->Send();
}

void IntakeForm::on_loadButton_clicked()
{
    qDebug() << "gui -> LOAD INTAKE FORM PRESSED";
    _asyncLoadIntake->GetMediatorArg().SetArg(&_currentIntake);
    _asyncLoadIntake->Send();
    testFunction();
    update();
}

void IntakeForm::on_clearButton_clicked()
{
    qDebug() << "gui -> CLEAR INTAKE FORM PRESSED";

}

// Save Intake Form Callback (result)
void IntakeForm::Recieve_SaveIntakeForm(MediatorArg arg)
{

}

// Load Intake Form Callback (result)
void IntakeForm::Recieve_LoadIntakeForm(MediatorArg arg)
{

}

// update the intakeform
void IntakeForm::update()
{
    partys[0]->SetPerson(_currentIntake.newParty());
    partys.push_back(new PartyDetailsForm());
    std::vector<Person *> tempPeople;
    tempPeople = _currentIntake.getParties();
    ui->OtherPartyTabWidget->clear();
    PartyDetailsForm *temp;
    for(uint i = 1; i < tempPeople.size(); i++)
    {
        temp = new PartyDetailsForm();
        temp->SetPerson(tempPeople[i]);
        ui->OtherPartyTabWidget->addTab(temp,QString::fromStdString("Party " + std::to_string((ui->OtherPartyTabWidget->count())+2)));
    }
}
// test function to load an intake class and populate the fields
void IntakeForm::testFunction()
{
    _currentIntake.clearRespondents();
    Intake temp;
    temp.clearRespondents();
    Person claimant = Person::SampleData();
    claimant.setFirstName("apple");
    temp.addClaimant(claimant);

    Person p1 = Person::SampleData();
    p1.setFirstName("peach");
    temp.addRespondents(p1);

    Person p2 = Person::SampleData();
    p2.setFirstName("banana");
    temp.addRespondents(p2);

    Person p3 = Person::SampleData();
    p3.setFirstName("grape");
    temp.addRespondents(p3);

    _currentIntake = temp;
}
// initilizes vector with one new party details form
void IntakeForm::initPartys()
{
    partys.push_back(new PartyDetailsForm());
    partys.at(0)->SetPerson(_currentIntake.newParty());
    partys.push_back(new PartyDetailsForm());
    partys.at(1)->SetPerson(_currentIntake.newParty());
    ui->mainPartyTabWidget->addTab(partys[0],"Party 1");
    ui->OtherPartyTabWidget->addTab(partys[1],"Party 2");
}
// adds a new tab to widget
void IntakeForm::on_addButton_clicked()
{
    partys.push_back(new PartyDetailsForm());
    partys.at(partys.size() - 1)->SetPerson(_currentIntake.newParty());
    ui->OtherPartyTabWidget->addTab(partys[partys.size() - 1], QString::fromStdString("Party " + std::to_string(ui->OtherPartyTabWidget->count()+2)));
    ui->OtherPartyTabWidget->setCurrentIndex(ui->OtherPartyTabWidget->count()-1);
    //update();
}
// removes a tab from widget
void IntakeForm::on_removeButton_clicked()
{
    partys.erase(partys.begin() + ui->OtherPartyTabWidget->currentIndex());
    ui->OtherPartyTabWidget->removeTab(ui->OtherPartyTabWidget->currentIndex());
}

int IntakeForm::totalParties()
{
    return (partys.size() + 1);
}

Intake IntakeForm::getCurrentIntake()
{
    return _currentIntake;
}
