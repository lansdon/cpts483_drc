#include "mediationsessionform.h"
#include "ui_mediationsessionform.h"
#include <QDebug>
#include "persondetailsform.h"
#include "drctypes.h"
#include "DRCModels.h"

MediationSessionForm::MediationSessionForm(QWidget *parent, MediationSession *session) :
    QWidget(parent),
    ui(new Ui::MediationSessionForm),
    _mediationSession(session ? session : new MediationSession())
{
    ui->setupUi(this);
    ui->dateTimeEdit->setVisible(false);

    FillingFields = false;
//    if(_mediationSessions->size() > 0)
    fillFields(_mediationSession);
//    ui->sessiontTableWidget->setCurrentCell(0,0);

}

MediationSessionForm::~MediationSessionForm()
{
    delete ui;
}

void MediationSessionForm::setMediationSession(MediationSession *session)
{
    _mediationSession = session;
    fillFields(_mediationSession);
}

void MediationSessionForm::setParties(int input)
{
//    ui->SupportTabWidget->clear();
//    _attorneyAndSupportVector->clear();
//    for(int i = 0; i < input;i++)
//    {
//        _attorneyAndSupportVector->push_back(new AttorneyAndSupportForMediationSessionView());
//        ui->SupportTabWidget->addTab(_attorneyAndSupportVector->at(i),QString::fromStdString("Party " + std::to_string(ui->SupportTabWidget->count() + 1)));

//    }
}

void MediationSessionForm::updateTabs(std::vector<Person *> *input)
{
//        qDebug() << "tab widget size " << ui->SupportTabWidget->count();
//        if(input->size() > (uint)ui->SupportTabWidget->count())
//        {
//            for(uint i = (ui->SupportTabWidget->count()); i < input->size(); i++)
//            {
//                qDebug() << i;
////                _attorneyAndSupportVector->push_back(new AttorneyAndSupportForMediationSessionView());
////                ui->SupportTabWidget->addTab(_attorneyAndSupportVector->at(i),QString::fromStdString("Party " + std::to_string(ui->SupportTabWidget->count() + 1)));
//            }
//        }
//        else
//        {
//            for(int i = input->size();i < ui->SupportTabWidget->count(); i++)
//                ui->SupportTabWidget->removeTab(ui->SupportTabWidget->count()-1);
//        }

//    qDebug() << "input size: " << input->size();
//    qDebug() << "attorney Vector size: " << _attorneyAndSupportVector->size();
//    if(input->size() == _attorneyAndSupportVector->size())
//    {
//        for(uint i = 0; i < _attorneyAndSupportVector->size(); i++)
//        {
//            qDebug() << i;
//            qDebug() << input->at(i)->getAttorney();
//            _attorneyAndSupportVector->at(i)->setAttorney((input->at(i)->getAttorney()));
//        }
//    }
}

void MediationSessionForm::on_CancelledRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _mediationSession->setCancelledRB(checked);
//        PopulateSessionTable();
    }
}

void MediationSessionForm::on_PendingRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _mediationSession->setPendingRB(checked);
//        PopulateSessionTable();
    }
}

void MediationSessionForm::on_confirmedRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _mediationSession->setConfirmedRB(checked);
//        PopulateSessionTable();
    }
}

void MediationSessionForm::on_rescheduledRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _mediationSession->setRescheduledRB(checked);
//        PopulateSessionTable();
    }
}

void MediationSessionForm::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(!FillingFields)
    {
        _mediationSession->setMediationTime(dateTime);
//        PopulateSessionTable();
    }
}

void MediationSessionForm::on_Fee1LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFee1(ui->Fee1LineEdit->text());
}

void MediationSessionForm::on_Fee1PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFee1Paid(checked);
}



void MediationSessionForm::fillFields(MediationSession *input)
{
    if(input)
    {
        FillingFields = true;
//        ui->CancelledRadioButton->setChecked(input->getCancelledRB());
//        ui->confirmedRadioButton->setChecked(input->getConfirmedRB());
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
//        ui->PendingRadioButton->setChecked(input->getPendingRB());
//        ui->rescheduledRadioButton->setChecked(input->getRescheduledRB());
        if(input->getObserver1()!=NULL)
            ui->Observe1LineEdit->setText(input->getObserver1()->FullName());
        if(input->getObserver2()!=NULL)
            ui->Observer2lineEdit->setText(input->getObserver2()->FullName());
        FillingFields = false;
    }
}

//void MediationSessionForm::on_sessiontTableWidget_doubleClicked(const QModelIndex &index)
//{
//    if((uint)index.row() > _mediationSessions->size() - 1 || _mediationSessions->size() == 0)
//    {
//        MediationSession *temp = new MediationSession();
//        _mediationSessions->push_back(temp);
//        configSessionTable();
//        PopulateSessionTable();
// //       ui->sessiontTableWidget->setCurrentCell(_mediationSessions->size()-1,0);
//        fillFields(_mediationSessions->at(_mediationSessions->size() - 1));
//    }

//}

void MediationSessionForm::on_Fee2LineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFee2(ui->Fee2LineEdit->text());
}

void MediationSessionForm::on_FamilyFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFeeFamily(ui->FamilyFeeLineEdit->text());
}

void MediationSessionForm::on_OtherFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _mediationSession->setFeeOther(ui->OtherFeeLineEdit->text());
}

void MediationSessionForm::on_Fee2PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFee2Paid(checked);
}

void MediationSessionForm::on_FamilyFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFeeFamilyPaid(checked);
}

void MediationSessionForm::on_OtherFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _mediationSession->setFeeOtherPaid(checked);
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

void MediationSessionForm::on_mediator1EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_mediationSession->getMediator1(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;

}

void MediationSessionForm::on_mediator2EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_mediationSession->getMediator2(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
}

void MediationSessionForm::on_observer1EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_mediationSession->getObserver1(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
}

void MediationSessionForm::on_observer2EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_mediationSession->getObserver2(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
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
