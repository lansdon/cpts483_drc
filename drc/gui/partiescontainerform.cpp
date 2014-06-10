#include "partiescontainerform.h"
#include "ui_partiescontainerform.h"
#include "DRCModels.h"
#include "partyform.h"

PartiesContainerForm::PartiesContainerForm(QWidget *parent, Party* party1, Party* party2)
    : QWidget(parent)
    , ui(new Ui::PartiesContainerForm)
{
    ui->setupUi(this);

    if(party1)
        SetParty1View(party1);
    if(party2)
        SetParty2View(party2);
}

PartiesContainerForm::~PartiesContainerForm()
{
    delete ui;
}

void PartiesContainerForm::SetParty1View(Party* party)
{
    // Testing
    if(!party)
    {
        party = Party::SampleData();
    }

    if(party)
    {
        QGridLayout* gLayout = new QGridLayout;
        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
        ui->party1Frame->setLayout(gLayout);
    }
}

void PartiesContainerForm::SetParty2View(Party* party)
{
    // Testing
    if(!party)
    {
        party = Party::SampleData();
    }

    if(party)
    {
        QGridLayout* gLayout = new QGridLayout;
        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
        ui->party2Frame->setLayout(gLayout);
    }
}
