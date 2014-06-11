#include "mediationprocessstatusform.h"
#include "ui_mediationprocessstatusform.h"

MediationProcessStatusForm::MediationProcessStatusForm(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessStatusForm),
    _mediationProcess(mediationProcess)
{
    ui->setupUi(this);

    Update();
}

void MediationProcessStatusForm::Update()
{
    ui->createdDateLabel->setText(_mediationProcess->GetCreationDate().toString("MM/dd/yyyy"));
    ui->statusComboBox->setCurrentIndex(_mediationProcess->GetCurrentState());
    ui->spanishCheckBox->setChecked(_mediationProcess->GetRequiresSpanish());
    ui->party1Fullname->setText(_mediationProcess->GetParty1()->GetPrimary().FullName());
    ui->party2Fullname->setText(_mediationProcess->GetParty2()->GetPrimary().FullName());

    ui->childrenEffectedLabel->setText(QString( _mediationProcess->GetAffectedChildrenCount()));
    ui->conflictComboBox->setCurrentIndex(_mediationProcess->GetDisputeType());
    ui->countyComboBox->setCurrentIndex(_mediationProcess->GetCountyId());

    ui->referralComboBox->setCurrentIndex(_mediationProcess->GetReferralType());
    ui->spanishCheckBox->setChecked(_mediationProcess->GetRequiresSpanish());

    foreach(auto note, _mediationProcess->GetNotes())
        ui->notesListWidget->addItem(note);

    // To do:     ui->updcomingDatesList



}

MediationProcessStatusForm::~MediationProcessStatusForm()
{
    delete ui;
}
