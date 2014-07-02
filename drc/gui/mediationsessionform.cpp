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

    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Fee1LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFee1(ui->Fee1LineEdit->text());
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Fee1PaidCheckBox_toggled(bool checked)
{
    _mediationSession->setFee1Paid(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
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
        ui->CreationDateDisplayLabel->setText(_mediationSession->GetCreatedDate().toString());
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
        ui->Mediator2LineEdit->setText(input->getMediator2());
        ui->MediatorLineEdit->setText(input->getMediator1());
        ui->Observe1LineEdit->setText(input->getObserver1());
        ui->Observer2lineEdit->setText(input->getObserver2());
        FillingFields = false;
    }
}

void MediationSessionForm::on_Fee2LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFee2(ui->Fee2LineEdit->text());
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_FamilyFeeLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFeeFamily(ui->FamilyFeeLineEdit->text());
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_OtherFeeLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFeeOther(ui->OtherFeeLineEdit->text());
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Fee2PaidCheckBox_toggled(bool checked)
{
    _mediationSession->setFee2Paid(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_FamilyFeePaidCheckBox_toggled(bool checked)
{
    _mediationSession->setFeeFamilyPaid(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_OtherFeePaidCheckBox_toggled(bool checked)
{
    _mediationSession->setFeeOtherPaid(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_incomeFee1LineEdit_textEdited(const QString &arg1)
{
   _mediationSession->setIncomeFee1(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_incomeFee2LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setIncomeFee2(ui->incomeFee2LineEdit->text());
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_incomeFeeFamilyLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setIncomeFeeFamily(ui->incomeFeeFamilyLineEdit->text());

    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
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
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_stateComboBox_currentIndexChanged(int index)
{
    _mediationSession->SetState((SessionStates)index);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_incomeFeeOtherLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setIncomeFeeOther(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_MediatorLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setMediator1(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Mediator2LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setMediator2(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Observe1LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setObserver1(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Observer2lineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setObserver2(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}
