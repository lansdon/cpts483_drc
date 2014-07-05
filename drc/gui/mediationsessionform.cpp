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

MediationSessionForm::MediationSessionForm(QWidget *parent, MediationSession *session) :
    QWidget(parent),
    ui(new Ui::MediationSessionForm),
    _mediationSession(session ? session : new MediationSession())
{
    ui->setupUi(this);
    ui->dateTimeEdit->setVisible(false);
    //_sessionData = new ClientSessionDataVector();
    for(int i = 0; i < 2; i++)
    {
        _sessionData.push_back(new ClientSessionData());
    }
    ConfigureComboBoxes();

    FillingFields = false;
    fillFields(_mediationSession);
    configureMediatorTable();
    configureAttyAndSupportTable();

    _mediatorid = Mediator::Register(MKEY_DOCK_SESSION_CHANGED, [this](MediatorArg arg){ SetSessionEvent(arg);});

    configureFeeTable();
    PopulateFeeTable();
}

MediationSessionForm::~MediationSessionForm()
{
    Mediator::Unregister(MKEY_DOCK_SESSION_CHANGED, _mediatorid);
    delete ui;
}

void MediationSessionForm::configureFeeTable()
{
    ui->feeDiplayTableWidget->setColumnCount(3);
    ui->feeDiplayTableWidget->setRowCount(3);
    QStringList header;
    header <<"Fee"<<"Paid"<<"Income";
    ui->feeDiplayTableWidget->setHorizontalHeaderLabels(header);

    // TEMP

}

void MediationSessionForm::PopulateFeeTable()
{
    // Samples:

    for(int i = 0; i < ui->feeDiplayTableWidget->rowCount(); ++i)
    {
        QComboBox *cb = new QComboBox();
       cb->addItems((QStringList() << "Item 1" << "Item 2" << "Item 3"));
       ui->feeDiplayTableWidget->setCellWidget(i,2,cb);
       connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(TestComboBoxIndexChanged(int)));

       QCheckBox *checkbox = new QCheckBox();
       ui->feeDiplayTableWidget->setCellWidget(i,1,checkbox);
       connect(checkbox, SIGNAL(toggled(bool)), this, SLOT(TestCheckBoxToggled(bool)));
    }

}

void MediationSessionForm::TestComboBoxIndexChanged(int value)
{
    QMessageBox mb;
    mb.setText("OMG");
    mb.setInformativeText("You changed the value!");
    mb.setStandardButtons(QMessageBox::Cancel);
    mb.exec();
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
    ui->attyAttendTableWidget->setColumnCount(1);
    ui->attyAttendTableWidget->setRowCount(1);
    QStringList header;
    header << "Attorney will attend   Attorney did attend   Support";
    //ui->attyAttendTableWidget->setHorizontalHeaderLabels(header);
    ui->attyAttendTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->attyAttendTableWidget->horizontalHeader()->setHidden(true);
    ui->attyAttendTableWidget->setCellWidget(0,0,new AttorneyHeaderView());
    ui->attyAttendTableWidget->setShowGrid(true);
}

void MediationSessionForm::populateAttyAndSupportTable()
{
    ui->attyAttendTableWidget->setRowCount(_sessionData.size() + 1);

    for(int i = 0; i < (int)_sessionData.size(); i++)
    {

//        QCheckBox *attySaid = new QCheckBox();
//        QCheckBox *attyDid = new QCheckBox();
//        QSpinBox *support = new QSpinBox();


////        attySaid->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
////        attySaid->setCheckState(Qt::Unchecked);
////        attyDid->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
////        attyDid->setCheckState(Qt::Unchecked);


//        ui->attyAttendTableWidget->setCellWidget(i,0,attySaid);
//        ui->attyAttendTableWidget->setCellWidget(i,1,attyDid);
//        ui->attyAttendTableWidget->setCellWidget(i,2,support);
//        for (int c = 0; c < ui->attyAttendTableWidget->horizontalHeader()->count(); ++c)
//        {
//           ui->attyAttendTableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
//        }
//        //ClientSessionData *temp = new ClientSessionData();
//        connect(attyDid, SIGNAL(toggled(bool)), this->_sessionData.at(i), SLOT(on_atty_did_attend(bool)));
//        connect(attySaid, SIGNAL(toggled(bool)), this->_sessionData.at(i), SLOT(on_atty_will_attend(bool)));
//        connect(support, SIGNAL(valueChanged(int)), this->_sessionData.at(i), SLOT(on_support(uint)));

        //_mediationSession->getClientSessionDataVector().push_back(temp);

//        attySaid->setFlags(Qt::NoItemFlags);
//        attyDid->setFlags(Qt::NoItemFlags);
        ui->attyAttendTableWidget->setCellWidget(i + 1,0,new AttorneySupportView());
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
