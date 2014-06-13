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
    p1 = new PartyForm();
    p2 = new PartyForm();
//    if(party1)
//        SetParty1View(party1);
//    if(party2)
//        SetParty2View(party2);
    QGridLayout* gLayout = new QGridLayout;
    gLayout->addWidget(p1);
//    ui->party1Frame->setLayout(gLayout);
    gLayout = new QGridLayout;
    gLayout->addWidget(p2);
//    ui->party2Frame->setLayout(gLayout);

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
//    foreach(Party* party, *parties)
//    {
//        party = Party::SampleData();
//    }

//    if(party)
//    {
////        QGridLayout* gLayout = new QGridLayout;
////        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
////        ui->party1Frame->setLayout(gLayout);
//        p1->setParty(party);
//    }
}

//void PartiesContainerForm::SetParty2View(Party* party)
//{
//    // Testing
//    if(!party)
//    {
//        party = Party::SampleData();
//    }

//    if(party)
//    {
////        QGridLayout* gLayout = new QGridLayout;
////        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
////        ui->party2Frame->setLayout(gLayout);
//        p2->setParty(party);
//    }
//}
//=======
////        QGridLayout* gLayout = new QGridLayout;
////        gLayout->addWidget(new PartyForm(ui->party1Frame, party));
//        ui->partyTabWidget->addTab(new PartyForm(this, party), party->GetPrimary().FullName());
//    }
//}

//>>>>>>> origin/GUI_Branch_5-30-14
