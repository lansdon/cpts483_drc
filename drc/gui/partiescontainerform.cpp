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
    if(parties)
    {
        ui->partyTabWidget->clear();
//        PartyFormVector.clear();
        foreach(Party* party, *parties)
        {
            if(party)
            {
                auto pForm = new PartyForm(ui->partyTabWidget, party);
                connect(pForm,SIGNAL(SaveSignaled()),this,SLOT(DoSaveSignal()));
                ui->partyTabWidget->addTab(pForm, party->GetPrimary()->FullName() );
//                PartyFormVector.push_back();
            }
        }
//        foreach(PartyForm* p, PartyFormVector)
//        {
//        }
    }
}

