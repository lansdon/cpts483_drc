#include "mediationsessionform.h"
#include "ui_mediationsessionform.h"
#include <QDebug>
#include "persondetailsform.h"
#include "drctypes.h"
#include "DRCModels.h"
#include "Mediator.h"
#include "mediationobserverview.h"
#include <QMessageBox>
#include <QSpinBox>
#include <QCheckBox>
#include "clientsessiondata.h"
#include "attorneysupportview.h"
#include "attorneyheaderview.h"
#include <QObject>

MediationSessionForm::MediationSessionForm(QWidget *parent, MediationSession *session) :
    QWidget(parent),
    ui(new Ui::MediationSessionForm),
    _mediationSession(session ? session : new MediationSession())
{
    ui->setupUi(this);
    ui->dateTimeEdit->setVisible(false);
    //_sessionData = new ClientSessionDataVector();

    ConfigureComboBoxes();

    FillingFields = false;
    fillFields(_mediationSession);
    configureMediatorTable();
    configureAttyAndSupportTable();

    _mediatorid = Mediator::Register(MKEY_DOCK_SESSION_CHANGED, [this](MediatorArg arg){ SetSessionEvent(arg);});

    configureFeeTable();

}

MediationSessionForm::~MediationSessionForm()
{
    Mediator::Unregister(MKEY_DOCK_SESSION_CHANGED, _mediatorid);
    delete ui;
}

void MediationSessionForm::configureFeeTable()
{
    ui->feeDiplayTableWidget->setColumnCount(3);
    ui->feeDiplayTableWidget->setRowCount(0);
    QStringList header;
    header <<"Fee"<<"Paid"<<"Income";
    ui->feeDiplayTableWidget->setHorizontalHeaderLabels(header);
    for (int c = 0; c < ui->feeDiplayTableWidget->horizontalHeader()->count(); ++c)
    {
       ui->feeDiplayTableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    // TEMP

}

void MediationSessionForm::PopulateFeeTable()
{
    // Samples:
     ui->feeDiplayTableWidget->setRowCount(_mediationSession->getClientSessionDataVector()->size());
    //QTableWidgetItem *proto = new QTableWidgetItem();

     for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size(); ++i)
    {

        QLineEdit *incomeLE = new QLineEdit();
        incomeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getIncome());
       //cb->addItems((QStringList() << "Item 1" << "Item 2" << "Item 3"));
       ui->feeDiplayTableWidget->setCellWidget(i,2,incomeLE);
       connect(incomeLE, SIGNAL(editingFinished()), this, SLOT(updateFromTable()));
       incomeLE->setMaximumSize(50,25);
       incomeLE->setAlignment(Qt::AlignCenter);
       //ui->feeDiplayTableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);

       QLineEdit *feeLE = new QLineEdit();
       feeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getFee());
      ui->feeDiplayTableWidget->setCellWidget(i,0,feeLE);
      connect(feeLE, SIGNAL(editingFinished()), this, SLOT(updateFromTable()));
        feeLE->setMaximumSize(50,25);
        feeLE->setAlignment(Qt::AlignCenter);

       QCheckBox *paidCB = new QCheckBox();
       paidCB->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getPaid());
       ui->feeDiplayTableWidget->setCellWidget(i,1,paidCB);
       connect(paidCB, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));


    }

}

void MediationSessionForm::updateFromTable()
{
//    QMessageBox mb;
//    mb.setText("OMG");
//    mb.setInformativeText("You changed the value!");
//    mb.setStandardButtons(QMessageBox::Cancel);
//    mb.exec();
    for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size();i++)
    {
        _mediationSession->getClientSessionDataVector()->at(i)->setFee(qobject_cast<QLineEdit*>(ui->feeDiplayTableWidget->cellWidget(i,0))->text());
        _mediationSession->getClientSessionDataVector()->at(i)->setPaid(qobject_cast<QCheckBox*>(ui->feeDiplayTableWidget->cellWidget(i,1))->isChecked());
        _mediationSession->getClientSessionDataVector()->at(i)->setIncome(qobject_cast<QLineEdit*>(ui->feeDiplayTableWidget->cellWidget(i,2))->text());
        _mediationSession->getClientSessionDataVector()->at(i)->setAttySaidAttend(qobject_cast<QCheckBox*>(ui->attyAttendTableWidget->cellWidget(i,0))->isChecked());
        _mediationSession->getClientSessionDataVector()->at(i)->setAttyDidAttend(qobject_cast<QCheckBox*>(ui->attyAttendTableWidget->cellWidget(i,1))->isChecked());
        _mediationSession->getClientSessionDataVector()->at(i)->setSupport(qobject_cast<QSpinBox*>(ui->attyAttendTableWidget->cellWidget(i,2))->value());
    }
}

void MediationSessionForm::TestCheckBoxToggled(bool value)
{
    QMessageBox mb;
    mb.setText("OMG");
    mb.setInformativeText("You changed the value = " + value);
    mb.setStandardButtons(QMessageBox::Cancel);
    mb.exec();
}

void MediationSessionForm::configureMediatorTable()
{
//    QStringList header;
//    header << "Mediator" << "Observer";
//    ui->MediatorDisplayTableView->setColumnCount(1);
//    ui->MediatorDisplayTableView->setRowCount(2);

//    ui->MediatorDisplayTableView->setHorizontalHeaderLabels({"Mediator            Observer"});
//    ui->MediatorDisplayTableView->setShowGrid(true);
//    for (int c = 0; c < ui->MediatorDisplayTableView->horizontalHeader()->count(); ++c)
//    {
//       ui->MediatorDisplayTableView->horizontalHeader()->setSectionResizeMode(
//            c, QHeaderView::Stretch);
//    }
//    ui->MediatorDisplayTableView->setCellWidget(0,0, new MediationObserverView());
//   // ui->MediatorDisplayTableView->setmi
//    ui->MediatorDisplayTableView->setCellWidget(1,0, new MediationObserverView());

    //ui->MediatorDisplayTableView->addItems(header);
    //ui->MediatorDisplayTableView->set(new QListWidgetItem(),new MediationObserverView());

}
void MediationSessionForm::configureAttyAndSupportTable()
{
    ui->attyAttendTableWidget->setColumnCount(3);
    ui->attyAttendTableWidget->setRowCount(0);
    QStringList header;
    header << "Attorney will attend" <<   "Attorney did attend" <<   "Support";
    ui->attyAttendTableWidget->setHorizontalHeaderLabels(header);
    //ui->attyAttendTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
   // ui->attyAttendTableWidget->horizontalHeader()->setHidden(true);
   // ui->attyAttendTableWidget->setCellWidget(0,0,new AttorneyHeaderView());
    ui->attyAttendTableWidget->setShowGrid(true);
    for (int c = 0; c < ui->attyAttendTableWidget->horizontalHeader()->count(); ++c)
    {
       ui->attyAttendTableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

void MediationSessionForm::populateAttyAndSupportTable()
{
    ui->attyAttendTableWidget->setRowCount(_mediationSession->getClientSessionDataVector()->size());

    for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size(); i++)
    {

        QCheckBox *attySaid = new QCheckBox();
        QCheckBox *attyDid = new QCheckBox();
        QSpinBox *support = new QSpinBox();


//        attySaid->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
//        attySaid->setCheckState(Qt::Unchecked);
//        attyDid->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
//        attyDid->setCheckState(Qt::Unchecked);
        attySaid->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getAttySaidAttend());
        attyDid->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getAttyDidAttend());
        support->setValue(_mediationSession->getClientSessionDataVector()->at(i)->getSupport());

        ui->attyAttendTableWidget->setCellWidget(i,0,attySaid);
        ui->attyAttendTableWidget->setCellWidget(i,1,attyDid);
        ui->attyAttendTableWidget->setCellWidget(i,2,support);

        //ClientSessionData *temp = new ClientSessionData();
        connect(attyDid, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));
        connect(attySaid, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));
        connect(support, SIGNAL(valueChanged(int)), this, SLOT(updateFromTable()));

        //_mediationSession->getClientSessionDataVector().push_back(temp);

//        attySaid->setFlags(Qt::NoItemFlags);
//        attyDid->setFlags(Qt::NoItemFlags);
//        ui->attyAttendTableWidget->setCellWidget(i + 1,0,new AttorneySupportView());
    }
//    _mediationSession->setClientSessionDataVector(*_sessionData);

    //ui->attyAttendListWidget->aaddWidget(0,0,new AttorneySupportView());
  //  ui->attyAttendListWidget->setCellWidget(1,0,new AttorneySupportView());
//   AttorneySupportView *myItem = new AttorneySupportView();
//   AttorneySupportView *myItem1 = new AttorneySupportView();
//   QListWidgetItem *item = new QListWidgetItem();
//   QListWidgetItem *item1 = new QListWidgetItem();

//   ui->attyAttendListWidget->addItem(item);
//   ui->attyAttendListWidget->addItem(item1);
//   ui->attyAttendListWidget->setItemWidget(item,myItem);
//   ui->attyAttendListWidget->setItemWidget(item1,myItem1);
}

void MediationSessionForm::setMediationSession(MediationSession *session)
{
    _mediationSession = session;

    populateAttyAndSupportTable();
    PopulateFeeTable();
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
    _mediationSession->setFee1(arg1);
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
//        ui->FamilyFeeLineEdit->setText(input->getFeeFamily());
//        ui->FamilyFeePaidCheckBox->setChecked(input->getFeeFamilyPaid());
//        ui->Fee1LineEdit->setText(input->getFee1());
//        ui->Fee2LineEdit->setText(input->getFee2());
//        ui->OtherFeeLineEdit->setText(input->getFeeOther());
//        ui->Fee1PaidCheckBox->setChecked(input->getFee1Paid());
//        ui->Fee2PaidCheckBox->setChecked(input->getFee2Paid());
//        ui->OtherFeePaidCheckBox->setChecked(input->getFeeOtherPaid());
//        ui->incomeFee1LineEdit->setText(input->getIncomeFee1());
//        ui->incomeFee2LineEdit->setText(input->getIncomeFee2());
//        ui->incomeFeeFamilyLineEdit->setText(input->getIncomeFeeFamily());
//        ui->incomeFeeOtherLineEdit->setText(input->getIncomeFeeOther());
//        ui->Mediator2LineEdit->setText(input->getMediator2());
//        ui->MediatorLineEdit->setText(input->getMediator1());
//        ui->Observe1LineEdit->setText(input->getObserver1());
//        ui->Observer2lineEdit->setText(input->getObserver2());
        FillingFields = false;
    }
}

void MediationSessionForm::on_Fee2LineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFee2(arg1);
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_FamilyFeeLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFeeFamily(arg1);
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_OtherFeeLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setFeeOther(arg1);
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
    _mediationSession->setIncomeFee2(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_incomeFeeFamilyLineEdit_textEdited(const QString &arg1)
{
    _mediationSession->setIncomeFeeFamily(arg1);
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
