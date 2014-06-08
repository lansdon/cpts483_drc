#include "partyform.h"
#include "ui_partyform.h"
#include "party.h"
#include "persondetailsform.h"
#include <QGridLayout>


PartyForm::PartyForm(QWidget *parent, Party* party) :
    QWidget(parent),
    ui(new Ui::PartyForm),
    _party(party ? _party : new Party())
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout();
//    PersonDetailsForm* primaryForm = new PersonDetailsForm(this);
    gridLayout->addWidget(new PersonDetailsForm(ui->primaryFrame, &_party->GetPrimary()));
    ui->primaryFrame->setLayout(gridLayout);
}

PartyForm::~PartyForm()
{
    delete ui;
}
