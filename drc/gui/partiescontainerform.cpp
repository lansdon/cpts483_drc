#include "partiescontainerform.h"
#include "ui_partiescontainerform.h"
#include "DRCModels.h"
#include "partyform.h"
#include "drctypes.h"
#include <QTabWidget>

PartiesContainerForm::PartiesContainerForm(QWidget *parent, PartyVector* parties)
    : QWidget(parent)
    , ui(new Ui::PartiesContainerForm)
{
    ui->setupUi(this);

    AddPartyTabs(parties);
}

PartiesContainerForm::~PartiesContainerForm()
{
    delete ui;
}

void PartiesContainerForm::AddPartyTabs(PartyVector* parties)
{
    // Testing
//    if(!party)
//    {
//        party = Party::SampleData();
//    }
    ui->partyTabWidget->clear();
    foreach(Party* party, *parties)
    {
//        QGridLayout* gLayout = new QGridLayout;
//        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
        ui->partyTabWidget->addTab(new PartyForm(this, party), party->GetPrimary().FullName());
    }
}

