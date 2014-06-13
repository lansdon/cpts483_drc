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
        PartyFormVector.clear();
        foreach(Party* party, *parties)
        {
            if(party)
            {
                PartyFormVector.push_back(new PartyForm(ui->partyTabWidget, party));



             }
        }
        foreach(PartyForm* p, PartyFormVector)
        {
            ui->partyTabWidget->addTab(p, p->getFullName() );
            connect(p,SIGNAL(PassItOn(Person*)),this,SLOT(savePersonContactFromFar(Person*)));
        }
    }
}

void PartiesContainerForm::savePersonContactFromFar(Person *value)
{
    PassItOnAgain(value);
}
