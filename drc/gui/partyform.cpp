#include "partyform.h"
#include "ui_partyform.h"
#include "party.h"
#include "persondetailsform.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>


PartyForm::PartyForm(QWidget *parent, Party* party) :
    QWidget(parent),
    ui(new Ui::PartyForm),
    _party(party ? party : new Party())
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout();
    PersonDetailsForm* personDetailsForm = new PersonDetailsForm(this, party->GetPrimary());
    connect(personDetailsForm,SIGNAL(SaveSignaled()),this,SLOT(DoSaveSignal()));
    connect(personDetailsForm,SIGNAL(EditSignaled()),this,SLOT(DoEditSignal()));
    gridLayout->addWidget(personDetailsForm);

    ui->primaryFrame->setLayout(gridLayout);

}


PartyForm::~PartyForm()
{
    delete ui;
}

void PartyForm::setParty(Party *value)
{
    _party = value;
    _personDetailsForm->SetPerson(_party->GetPrimary());
}


