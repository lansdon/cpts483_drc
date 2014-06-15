#include "mediationprocessstatusform.h"
#include "ui_mediationprocessstatusform.h"

MediationProcessStatusForm::MediationProcessStatusForm(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessStatusForm),
    _mediationProcess(mediationProcess)
{
    ui->setupUi(this);

    ConfigureComboBoxes();

    Update();
}

MediationProcessStatusForm::~MediationProcessStatusForm()
{
    delete ui;
}

void MediationProcessStatusForm::Update()
{
    ui->createdDateLabel->setText(_mediationProcess->GetCreationDate().toString("MM/dd/yyyy"));
    ui->statusComboBox->setCurrentIndex(_mediationProcess->GetCurrentState());
    ui->spanishCheckBox->setChecked(_mediationProcess->GetRequiresSpanish());
    ui->party1Fullname->setText(_mediationProcess->GetParty1()->GetPrimary().FullName());
    ui->party2Fullname->setText(_mediationProcess->GetParty2()->GetPrimary().FullName());

    ui->childrenEffectedLabel1->setText(QString( _mediationProcess->GetParty1()->GetAffectedChildren()));
    ui->childrenEffectedLabel2->setText(QString( _mediationProcess->GetParty2()->GetAffectedChildren()));
    ui->conflictComboBox->setCurrentIndex(_mediationProcess->GetDisputeType());
    ui->countyComboBox->setCurrentIndex(_mediationProcess->GetCountyId());
    ui->referralComboBox->setCurrentIndex(_mediationProcess->GetReferralType());
    ui->spanishCheckBox->setChecked(_mediationProcess->GetRequiresSpanish());

    foreach(auto note, _mediationProcess->GetNotes())
        ui->notesListWidget->addItem(note);

    // To do:     ui->updcomingDatesList



}

// Sets the values based on enums.
void MediationProcessStatusForm::ConfigureComboBoxes()
{
    ui->conflictComboBox->setItemText(DISPUTE_T_NONE, StringForDisputeTypes(DISPUTE_T_NONE));
    ui->conflictComboBox->setItemText(DISPUTE_T_PARENTING_PLAN, StringForDisputeTypes(DISPUTE_T_PARENTING_PLAN));
    ui->conflictComboBox->setItemText(DISPUTE_T_DIVORCE, StringForDisputeTypes(DISPUTE_T_DIVORCE));
    ui->conflictComboBox->setItemText(DISPUTE_T_SMALL_CLAIMS, StringForDisputeTypes(DISPUTE_T_SMALL_CLAIMS));
    ui->conflictComboBox->setItemText(DISPUTE_T_TENANT, StringForDisputeTypes(DISPUTE_T_TENANT));
    ui->conflictComboBox->setItemText(DISPUTE_T_LANDLORD, StringForDisputeTypes(DISPUTE_T_LANDLORD));
    ui->conflictComboBox->setItemText(DISPUTE_T_CONSUMER_MERCHANT, StringForDisputeTypes(DISPUTE_T_CONSUMER_MERCHANT));
    ui->conflictComboBox->setItemText(DISPUTE_T_WORKPLACE, StringForDisputeTypes(DISPUTE_T_WORKPLACE));
    ui->conflictComboBox->setItemText(DISPUTE_T_NEIGHBORHOOD, StringForDisputeTypes(DISPUTE_T_NEIGHBORHOOD));
    ui->conflictComboBox->setItemText(DISPUTE_T_FAMILY, StringForDisputeTypes(DISPUTE_T_FAMILY));
    ui->conflictComboBox->setItemText(DISPUTE_T_PROPERTY_BUSINESS, StringForDisputeTypes(DISPUTE_T_PROPERTY_BUSINESS));
    ui->conflictComboBox->setItemText(DISPUTE_T_PARENT_TEEN, StringForDisputeTypes(DISPUTE_T_PARENT_TEEN));
    ui->conflictComboBox->setItemText(DISPUTE_T_VICTIM_OFFENDER, StringForDisputeTypes(DISPUTE_T_VICTIM_OFFENDER));
    ui->conflictComboBox->setItemText(DISPUTE_T_OTHER, StringForDisputeTypes(DISPUTE_T_OTHER));

    ui->countyComboBox->setItemText(COUNTY_NONE, StringForCountyIds(COUNTY_NONE));
    ui->countyComboBox->setItemText(COUNTY_BENTON, StringForCountyIds(COUNTY_BENTON));
    ui->countyComboBox->setItemText(COUNTY_FRANLKIN, StringForCountyIds(COUNTY_FRANLKIN));
    ui->countyComboBox->setItemText(COUNTY_GRANT, StringForCountyIds(COUNTY_GRANT));
    ui->countyComboBox->setItemText(COUNTY_ADAMS, StringForCountyIds(COUNTY_ADAMS));
    ui->countyComboBox->setItemText(COUNTY_OTHER, StringForCountyIds(COUNTY_OTHER));

    ui->referralComboBox->setItemText(REFERRAL_T_NONE, StringForReferralTypes(REFERRAL_T_NONE));
    ui->referralComboBox->setItemText(REFERRAL_T_FAMILY_FRIEND, StringForReferralTypes(REFERRAL_T_FAMILY_FRIEND));
    ui->referralComboBox->setItemText(REFERRAL_T_ATTORNEY, StringForReferralTypes(REFERRAL_T_ATTORNEY));
    ui->referralComboBox->setItemText(REFERRAL_T_LEGAL_SERVICES, StringForReferralTypes(REFERRAL_T_LEGAL_SERVICES));
    ui->referralComboBox->setItemText(REFERRAL_T_RETURN_CLIENTS, StringForReferralTypes(REFERRAL_T_RETURN_CLIENTS));
    ui->referralComboBox->setItemText(REFERRAL_T_PRIVATE_AGENCY, StringForReferralTypes(REFERRAL_T_PRIVATE_AGENCY));
    ui->referralComboBox->setItemText(REFERRAL_T_COURTS, StringForReferralTypes(REFERRAL_T_COURTS));
    ui->referralComboBox->setItemText(REFERRAL_T_COURT_SOLICITED, StringForReferralTypes(REFERRAL_T_COURT_SOLICITED));
    ui->referralComboBox->setItemText(REFERRAL_T_LAW_ENFORCEMENT, StringForReferralTypes(REFERRAL_T_LAW_ENFORCEMENT));
    ui->referralComboBox->setItemText(REFERRAL_T_DCFS_JJC_GOVT_AGENCY, StringForReferralTypes(REFERRAL_T_DCFS_JJC_GOVT_AGENCY));
    ui->referralComboBox->setItemText(REFERRAL_T_ATTORNEY_GENERALS_OFFICE, StringForReferralTypes(REFERRAL_T_ATTORNEY_GENERALS_OFFICE));
    ui->referralComboBox->setItemText(REFERRAL_T_PRESENTATION_TRAINING, StringForReferralTypes(REFERRAL_T_PRESENTATION_TRAINING));
    ui->referralComboBox->setItemText(REFERRAL_T_ADVERTISING, StringForReferralTypes(REFERRAL_T_ADVERTISING));
    ui->referralComboBox->setItemText(REFERRAL_T_PHONEBOOK, StringForReferralTypes(REFERRAL_T_PHONEBOOK));
    ui->referralComboBox->setItemText(REFERRAL_T_INTERNET, StringForReferralTypes(REFERRAL_T_INTERNET));
    ui->referralComboBox->setItemText(REFERRAL_T_OTHER_NONE, StringForReferralTypes(REFERRAL_T_OTHER_NONE));

}


