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
    _loading = true;
    //ui->dateTimeEdit->setVisible(false);
    //_sessionData = new ClientSessionDataVector();

    ConfigureComboBoxes();
    configureMediatorTable();
    configureAttyAndSupportTable();

    _mediatorid = Mediator::Register(MKEY_DOCK_SESSION_CHANGED, [this](MediatorArg arg){ SetSessionEvent(arg);});

    configureFeeTable();
    FillingFields = false;
    fillFields(_mediationSession);
    _loading = false;
}

MediationSessionForm::~MediationSessionForm()
{
    Mediator::Unregister(MKEY_DOCK_SESSION_CHANGED, _mediatorid);
    delete ui;
}

void MediationSessionForm::configureFeeTable()
{
    ui->feeDiplayTableWidget->setColumnCount(5);
    ui->feeDiplayTableWidget->setRowCount(0);
    QStringList header;
    header << "Fee" << "Paid" << "Income" << "At Table" << "On Phone";
    ui->feeDiplayTableWidget->setHorizontalHeaderLabels(header);
    for (int c = 0; c < ui->feeDiplayTableWidget->horizontalHeader()->count(); ++c)
    {
       ui->feeDiplayTableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    // TEMP

}

void MediationSessionForm::PopulateFeeTable()
{
    _loading = true;
    // Samples:
    if(_mediationSession->getClientSessionDataVector()->size() == 0)
        return;
    ui->feeDiplayTableWidget->setRowCount(_mediationSession->getClientSessionDataVector()->size());
    //QTableWidgetItem *proto = new QTableWidgetItem();
    QStringList vertHeader;
  // layout->setAlignment(Qt::AlignCenter);
     for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size(); ++i)
    {
         vertHeader << ("Client " + QString::number(i + 1));
        QLineEdit *incomeLE = new QLineEdit();

        incomeLE->setMaxLength(50);
        incomeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getIncome());
       //cb->addItems((QStringList() << "Item 1" << "Item 2" << "Item 3"));
       ui->feeDiplayTableWidget->setCellWidget(i,2,incomeLE);
       connect(incomeLE, SIGNAL(textEdited(QString)), this, SLOT(updateFromTable()));
       connect(incomeLE, SIGNAL(editingFinished()), this, SLOT(editFinished()));
       incomeLE->setMaximumSize(50,25);
       incomeLE->setAlignment(Qt::AlignCenter);
       //ui->feeDiplayTableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);

       QLineEdit *feeLE = new QLineEdit();
       feeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getFee());
       feeLE->setMaxLength(50);
      ui->feeDiplayTableWidget->setCellWidget(i,0,feeLE);
      connect(feeLE, SIGNAL(textEdited(QString)), this, SLOT(updateFromTable()));
      connect(feeLE, SIGNAL(editingFinished()), this, SLOT(editFinished()));
        feeLE->setMaximumSize(50,25);
        feeLE->setAlignment(Qt::AlignCenter);

       QCheckBox *paidCB = new QCheckBox();
       paidCB->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getPaid());
       ui->feeDiplayTableWidget->setCellWidget(i,1,paidCB);
       connect(paidCB, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));

       QCheckBox *atTableCB = new QCheckBox();
       atTableCB->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getAtTable());
       ui->feeDiplayTableWidget->setCellWidget(i,3,atTableCB);
       connect(atTableCB, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));

       QCheckBox *onPhoneCB = new QCheckBox();
       onPhoneCB->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getOnPhone());
       ui->feeDiplayTableWidget->setCellWidget(i,4,onPhoneCB);
       connect(onPhoneCB, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));


    }
//     for(int i = (int)_mediationSession->getClientSessionDataVector()->size() - 2; i < (int)_mediationSession->getClientSessionDataVector()->size(); i ++)
//     {
//         QLineEdit *incomeLE = new QLineEdit();


//         incomeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getIncome());
//        //cb->addItems((QStringList() << "Item 1" << "Item 2" << "Item 3"));
//        ui->feeDiplayTableWidget->setCellWidget(i,2,incomeLE);
//        connect(incomeLE, SIGNAL(editingFinished()), this, SLOT(updateFromTable()));
//        incomeLE->setMaximumSize(50,25);
//        incomeLE->setAlignment(Qt::AlignCenter);
//        //ui->feeDiplayTableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);

//        QLineEdit *feeLE = new QLineEdit();
//        feeLE->setText(_mediationSession->getClientSessionDataVector()->at(i)->getFee());
//       ui->feeDiplayTableWidget->setCellWidget(i,0,feeLE);
//       connect(feeLE, SIGNAL(editingFinished()), this, SLOT(updateFromTable()));
//         feeLE->setMaximumSize(50,25);
//         feeLE->setAlignment(Qt::AlignCenter);

//        QCheckBox *paidCB = new QCheckBox();
//        paidCB->setChecked(_mediationSession->getClientSessionDataVector()->at(i)->getPaid());
//        ui->feeDiplayTableWidget->setCellWidget(i,1,paidCB);
//        connect(paidCB, SIGNAL(toggled(bool)), this, SLOT(updateFromTable()));

//     }
//     vertHeader << "Family" << "Other";
    ui->feeDiplayTableWidget->setVerticalHeaderLabels(vertHeader);
     _loading = false;
}

void MediationSessionForm::editFinished()
{
    if(_loading) return;
    updateFromTable();
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    fillFields(_mediationSession);
}

void MediationSessionForm::updateFromTable()
{
//    QMessageBox mb;
//    mb.setText("OMG");
//    mb.setInformativeText("You changed the value!");
//    mb.setStandardButtons(QMessageBox::Cancel);
//    mb.exec();
    if(_loading) return;
        for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size();i++)
        {
            _mediationSession->getClientSessionDataVector()->at(i)->setFee(qobject_cast<QLineEdit*>(ui->feeDiplayTableWidget->cellWidget(i,0))->text());
            _mediationSession->getClientSessionDataVector()->at(i)->setPaid(qobject_cast<QCheckBox*>(ui->feeDiplayTableWidget->cellWidget(i,1))->isChecked());
            _mediationSession->getClientSessionDataVector()->at(i)->setIncome(qobject_cast<QLineEdit*>(ui->feeDiplayTableWidget->cellWidget(i,2))->text());
            _mediationSession->getClientSessionDataVector()->at(i)->setAttySaidAttend(qobject_cast<QCheckBox*>(ui->attyAttendTableWidget->cellWidget(i,0))->isChecked());
            _mediationSession->getClientSessionDataVector()->at(i)->setAttyDidAttend(qobject_cast<QCheckBox*>(ui->attyAttendTableWidget->cellWidget(i,1))->isChecked());
            _mediationSession->getClientSessionDataVector()->at(i)->setSupport(qobject_cast<QSpinBox*>(ui->attyAttendTableWidget->cellWidget(i,2))->value());
            _mediationSession->getClientSessionDataVector()->at(i)->setAtTable(qobject_cast<QCheckBox*>(ui->feeDiplayTableWidget->cellWidget(i,3))->isChecked());
            _mediationSession->getClientSessionDataVector()->at(i)->setOnPhone(qobject_cast<QCheckBox*>(ui->feeDiplayTableWidget->cellWidget(i,4))->isChecked());
        }
        if((int)_mediationSession->getClientSessionDataVector()->size() > 0)
        {
            _mediationSession->setMediator1(qobject_cast<QLineEdit*>(ui->MediatorDisplayTableView->cellWidget(0,0))->text());
            _mediationSession->setObserver1(qobject_cast<QLineEdit*>(ui->MediatorDisplayTableView->cellWidget(0,1))->text());
            _mediationSession->setMediator2(qobject_cast<QLineEdit*>(ui->MediatorDisplayTableView->cellWidget(1,0))->text());
            _mediationSession->setObserver2(qobject_cast<QLineEdit*>(ui->MediatorDisplayTableView->cellWidget(1,1))->text());

            Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
            //fillFields(_mediationSession);
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
    QStringList header;
    header << "Mediator" << "Observer";
    ui->MediatorDisplayTableView->setColumnCount(2);
    ui->MediatorDisplayTableView->setRowCount(2);

    ui->MediatorDisplayTableView->setHorizontalHeaderLabels(header);
    ui->MediatorDisplayTableView->setShowGrid(true);
    for (int c = 0; c < ui->MediatorDisplayTableView->horizontalHeader()->count(); ++c)
    {
       ui->MediatorDisplayTableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

}
void MediationSessionForm::populateMediatorTable()
{
    _loading = true;
        QLineEdit *mediator1 = new QLineEdit();
        QLineEdit *observer1 = new QLineEdit();
        QLineEdit *mediator2 = new QLineEdit();
        QLineEdit *observer2 = new QLineEdit();
        mediator1->setMaxLength(50);
        mediator2->setMaxLength(50);
        observer1->setMaxLength(50);
        observer2->setMaxLength(50);
        mediator1->setText(_mediationSession->getMediator1());
        mediator2->setText(_mediationSession->getMediator2());
        observer1->setText(_mediationSession->getObserver1());
        observer2->setText(_mediationSession->getObserver2());
        ui->MediatorDisplayTableView->setCellWidget(0,0, mediator1);
        ui->MediatorDisplayTableView->setCellWidget(0,1, observer1);
        ui->MediatorDisplayTableView->setCellWidget(1,0, mediator2);
        ui->MediatorDisplayTableView->setCellWidget(1,1, observer2);
        connect(mediator1,SIGNAL(textEdited(QString)),this, SLOT(updateFromTable()));
        connect(observer1,SIGNAL(textEdited(QString)),this, SLOT(updateFromTable()));
        connect(mediator2,SIGNAL(textEdited(QString)),this, SLOT(updateFromTable()));
        connect(observer2,SIGNAL(textEdited(QString)),this, SLOT(updateFromTable()));
        connect(mediator1, SIGNAL(editingFinished()), this, SLOT(editFinished()));
        connect(observer1, SIGNAL(editingFinished()), this, SLOT(editFinished()));
        connect(mediator2, SIGNAL(editingFinished()), this, SLOT(editFinished()));
        connect(observer2, SIGNAL(editingFinished()), this, SLOT(editFinished()));

     _loading = false;
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
    _loading = true;
    if(_mediationSession->getClientSessionDataVector()->size() == 0)
        return;
    ui->attyAttendTableWidget->setRowCount(_mediationSession->getClientSessionDataVector()->size());
    QStringList vertHeader;
    for(int i = 0; i < (int)_mediationSession->getClientSessionDataVector()->size(); i++)
    {
        vertHeader << ("Client " + QString::number(i + 1));
        QCheckBox *attySaid = new QCheckBox();
        QCheckBox *attyDid = new QCheckBox();
        QSpinBox *support = new QSpinBox();
        //ui->attyAttendTableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

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
    ui->attyAttendTableWidget->setVerticalHeaderLabels(vertHeader);
   // ui->attyAttendTableWidget->verticalHeader()->setFixedWidth(50);
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
     _loading = false;
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
    if(_loading) return;
    if(!FillingFields)
    {
        _mediationSession->setMediationTime(dateTime);
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
}





void MediationSessionForm::fillFields(MediationSession *input)
{
    _loading = true;
    if(input)
    {
        _mediationSession = input;
        FillingFields = true;
        ui->stateComboBox->setCurrentIndex(_mediationSession->GetState());
//        ui->supportNumComboBox->setCurrentIndex(_mediationSession->GetSupportCount());
        ui->feePaidDisplayLabel->setText(_mediationSession->getFeeStatus());
//        ui->dateTimeEdit->setDateTime(input->getMediationTime());
//        ui->dateTimeEdit->setVisible(true);
        ui->dateEdit->setDate(_mediationSession->getScheduledDate());
        ui->timeEdit->setTime(_mediationSession->getScheduledTime());
//        ui->CreationDateDisplayLabel->setText(_mediationSession->GetCreatedDate().toString());
        ui->outcomeComboBox->setCurrentIndex(_mediationSession->getOutcome());
        ui->shuttleCheckBox->setChecked(_mediationSession->GetIsShuttle());
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
    populateAttyAndSupportTable();
    PopulateFeeTable();
    populateMediatorTable();
     _loading = false;
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
    // session schedule state
    for(int i=0; i<4; ++i)
        ui->stateComboBox->addItem("");

    ui->stateComboBox->setItemText(SESSION_STATE_CANCELLED, StringForSessionStates(SESSION_STATE_CANCELLED));
    ui->stateComboBox->setItemText(SESSION_STATE_CONFIRMED, StringForSessionStates(SESSION_STATE_CONFIRMED));
    ui->stateComboBox->setItemText(SESSION_STATE_NONE, StringForSessionStates(SESSION_STATE_NONE));
    ui->stateComboBox->setItemText(SESSION_STATE_PENDING, StringForSessionStates(SESSION_STATE_PENDING));
    ui->stateComboBox->setItemText(SESSION_STATE_RESCHEDULED, StringForSessionStates(SESSION_STATE_RESCHEDULED));


    // outcome combo box
    for(int i = 0; i < 9; i++)
        ui->outcomeComboBox->addItem("");

    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_NONE, StringForSessionOutcomes(SESSION_OUTCOME_NONE));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_FIRST_PARTY_WITHDREW,StringForSessionOutcomes(SESSION_OUTCOME_FIRST_PARTY_WITHDREW));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_SECOND_PARTY_DECLINES, StringForSessionOutcomes(SESSION_OUTCOME_SECOND_PARTY_DECLINES));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_AGREEMENT,  StringForSessionOutcomes(SESSION_OUTCOME_AGREEMENT));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_NO_AGREEMENT, StringForSessionOutcomes(SESSION_OUTCOME_NO_AGREEMENT));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_PROBLEM_SOLVING, StringForSessionOutcomes(SESSION_OUTCOME_PROBLEM_SOLVING));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_REFERRED_OUT, StringForSessionOutcomes(SESSION_OUTCOME_REFERRED_OUT));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_CANNOT_REACH_PARTIES, StringForSessionOutcomes(SESSION_OUTCOME_CANNOT_REACH_PARTIES));
    ui->outcomeComboBox->setItemText(SESSION_OUTCOME_SELF_RESOLVED, StringForSessionOutcomes(SESSION_OUTCOME_SELF_RESOLVED));
}



void MediationSessionForm::on_stateComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
    if(_mediationSession->GetState() == (SessionStates)index) return;
    _mediationSession->SetState((SessionStates)index);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}



void MediationSessionForm::on_MediatorLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    if(_mediationSession->getMediator1() == arg1) return;
    _mediationSession->setMediator1(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Mediator2LineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    if(_mediationSession->getMediator2() == arg1) return;
    _mediationSession->setMediator2(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Observe1LineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    if(_mediationSession->getObserver1() == arg1) return;
    _mediationSession->setObserver1(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_Observer2lineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    if(_mediationSession->getObserver2() == arg1) return;
    _mediationSession->setObserver2(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_dateEdit_userDateChanged(const QDate &date)
{
    if(_loading) return;
    if(_mediationSession->getScheduledDate() == date) return;
    _mediationSession->setScheduledDate(date);
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationSessionForm::on_timeEdit_userTimeChanged(const QTime &time)
{
    if(_loading) return;
    if(_mediationSession->getScheduledTime() == time) return;
    _mediationSession->setScheduledTime(time);
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);

}

void MediationSessionForm::on_outcomeComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
    if(_mediationSession->getOutcome() == (SessionOutcomes)index) return;
    _mediationSession->setOutcome((SessionOutcomes)index);
     Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);

}

void MediationSessionForm::on_shuttleCheckBox_toggled(bool checked)
{
    if(_loading) return;
    if(_mediationSession->GetIsShuttle() == checked) return;
    _mediationSession->SetIsShuttle(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);

}
