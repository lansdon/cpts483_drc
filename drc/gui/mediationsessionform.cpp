#include "mediationsessionform.h"
#include "ui_mediationsessionform.h"
#include <QDebug>
#include "persondetailsform.h"
#include "drctypes.h"
#include "DRCModels.h"
#include "Mediator.h"

MediationSessionForm::MediationSessionForm(QWidget *parent, MediationSession *session) :
    QWidget(parent),
    ui(new Ui::MediationSessionForm),
    _mediationSession(session ? session : new MediationSession())
{
    ui->setupUi(this);
    ui->dateTimeEdit->setVisible(false);

    ConfigureComboBoxes();

    FillingFields = false;
    fillFields(_mediationSession);

    _mediatorid = Mediator::Register(MKEY_DOCK_SESSION_CHANGED, [this](MediatorArg arg){ SetSessionEvent(arg);});
}

MediationSessionForm::~MediationSessionForm()
{
    Mediator::Unregister(MKEY_DOCK_SESSION_CHANGED, _mediatorid);
    delete ui;
}

void MediationSessionForm::setMediationSession(MediationSession *session)
{
    _mediationSession = session;
    fillFields(_mediationSession);
}

void MediationSessionForm::SetSessionEvent(MediatorArg arg)
{
    qDebug() << "SessionForm this = " << this;
    auto session = arg.getArg<MediationSession*>();
    if(session)
        setMediationSession(session);
}

void MediationSessionForm::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(!FillingFields)
    {
        _mediationSession->setMediationTime(dateTime);
    }
}

void MediationSessionForm::on_Fee1LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFee1(ui->Fee1LineEdit->text());
     fillFields(_mediationSession);
}

void MediationSessionForm::on_Fee1PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFee1Paid(checked);
    fillFields(_mediationSession);
}

void MediationSessionForm::fillFields(MediationSession *input)
{
    if(input)
    {
        _mediationSession = input;
        FillingFields = true;
        ui->stateComboBox->setCurrentIndex(_mediationSession->GetState());
        ui->supportNumComboBox->setCurrentIndex(_mediationSession->GetSupportCount());
        ui->feePaidDisplayLabel->setText(_mediationSession->getFeeStatus());
        ui->dateTimeEdit->setDateTime(input->getMediationTime());
        ui->dateTimeEdit->setVisible(true);
        ui->CreationDateDisplayLabel->setText(_mediationSession->getMediationCreation().toString());
        ui->FamilyFeeLineEdit->setText(input->getFeeFamily());
        ui->FamilyFeePaidCheckBox->setChecked(input->getFeeFamilyPaid());
        ui->Fee1LineEdit->setText(input->getFee1());
        ui->Fee2LineEdit->setText(input->getFee2());
        ui->OtherFeeLineEdit->setText(input->getFeeOther());
        ui->Fee1PaidCheckBox->setChecked(input->getFee1Paid());
        ui->Fee2PaidCheckBox->setChecked(input->getFee2Paid());
        ui->OtherFeePaidCheckBox->setChecked(input->getFeeOtherPaid());
        ui->incomeFee1LineEdit->setText(input->getIncomeFee1());
        ui->incomeFee2LineEdit->setText(input->getIncomeFee2());
        ui->incomeFeeFamilyLineEdit->setText(input->getIncomeFeeFamily());
        ui->incomeFeeOtherLineEdit->setText(input->getIncomeFeeOther());
        if(input->getMediator1()!=NULL)
            ui->Mediator2LineEdit->setText(input->getMediator2()->FullName());
        if(input->getMediator2()!=NULL)
            ui->MediatorLineEdit->setText(input->getMediator1()->FullName());
        if(input->getObserver1()!=NULL)
            ui->Observe1LineEdit->setText(input->getObserver1()->FullName());
        if(input->getObserver2()!=NULL)
            ui->Observer2lineEdit->setText(input->getObserver2()->FullName());
        FillingFields = false;
    }
}

void MediationSessionForm::on_Fee2LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFee2(ui->Fee2LineEdit->text());
     fillFields(_mediationSession);
}

void MediationSessionForm::on_FamilyFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFeeFamily(ui->FamilyFeeLineEdit->text());
     fillFields(_mediationSession);
}

void MediationSessionForm::on_OtherFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFeeOther(ui->OtherFeeLineEdit->text());
     fillFields(_mediationSession);
}

void MediationSessionForm::on_Fee2PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFee2Paid(checked);
    fillFields(_mediationSession);
}

void MediationSessionForm::on_FamilyFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFeeFamilyPaid(checked);
    fillFields(_mediationSession);
}

void MediationSessionForm::on_OtherFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFeeOtherPaid(checked);
    fillFields(_mediationSession);
}

void MediationSessionForm::on_incomeFee1LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setIncomeFee1(ui->incomeFee1LineEdit->text());
}

void MediationSessionForm::on_incomeFee2LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setIncomeFee2(ui->incomeFee2LineEdit->text());
}

void MediationSessionForm::on_incomeFeeFamilyLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setIncomeFeeFamily(ui->incomeFeeFamilyLineEdit->text());
}

void MediationSessionForm::on_incomeFeeOtherLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setIncomeFeeOther(ui->incomeFeeOtherLineEdit->text());
}

void MediationSessionForm::savePersonContact(Person *value)
{
    if(value)
        fillFields(_mediationSession);
}

void MediationSessionForm::deletePersonContact(Person *value)
{
    if(value)
        fillFields(_mediationSession);
}


// When a child has signaled a save event
void MediationSessionForm::SaveSignaled()
{

}

// When a child has signaled an edit was made.
void MediationSessionForm::EditSignaled()
{

}


// Sets the values based on enums.
void MediationSessionForm::ConfigureComboBoxes()
{
    for(int i=0; i<4; ++i)
        ui->stateComboBox->addItem("");

    ui->stateComboBox->setItemText(SESSION_STATE_CANCELLED, StringForSessionStates(SESSION_STATE_CANCELLED));
    ui->stateComboBox->setItemText(SESSION_STATE_CONFIRMED, StringForSessionStates(SESSION_STATE_CONFIRMED));
    ui->stateComboBox->setItemText(SESSION_STATE_NONE, StringForSessionStates(SESSION_STATE_NONE));
    ui->stateComboBox->setItemText(SESSION_STATE_PENDING, StringForSessionStates(SESSION_STATE_PENDING));
    ui->stateComboBox->setItemText(SESSION_STATE_RESCHEDULED, StringForSessionStates(SESSION_STATE_RESCHEDULED));
}

void MediationSessionForm::on_supportNumComboBox_currentIndexChanged(int index)
{
    _mediationSession->setSupportCount(index);
}
