#include "mediationsession.h"
#include "ui_mediationsession.h"
#include <QDebug>
#include "persondetailsform.h"

MediationSession::MediationSession(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationSession)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setVisible(false);
    for(int i = 0; i < 3; i++)
    {
        MediationSessionClass a;
        a = a.SampleData();
        _localMediationSessionClassVector.push_back(a);
    }
    configSessionTable();
    PopulateSessionTable();
    sessionCurrentRow = 0;
    FillingFields = false;
    fillFields(_localMediationSessionClassVector[sessionCurrentRow]);
    ui->sessiontTableWidget->setCurrentCell(0,0);

}

MediationSession::~MediationSession()
{
    delete ui;
}
void MediationSession::setParties(int input)
{
    ui->SupportTabWidget->clear();
    _attorneyAndSupportVector.clear();
    for(int i = 0; i < input;i++)
    {
        _attorneyAndSupportVector.push_back(new AttorneyAndSupportForMediationSessionView());
        ui->SupportTabWidget->addTab(_attorneyAndSupportVector.at(i),QString::fromStdString("Party " + std::to_string(ui->SupportTabWidget->count() + 1)));

    }
}

void MediationSession::updateTabs(std::vector<Person *> input)
{
//    AttorneyAndSupportForMediationSessionView *_attorneyAndSupport;
//    ui->tabWidget_2->clear();
//    for(uint i = 0; i < input.size();i++)
//    {
//        _attorneyAndSupport = new AttorneyAndSupportForMediationSessionView();
//        _attorneyAndSupport->setAttorney(QString::fromStdString(input[i].getAttorney()));
//            qDebug() << QString::fromStdString(input[i].getAttorney());

//            ui->tabWidget_2->addTab(_attorneyAndSupport, QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));


//    }
//    ui->tabWidget_2->repaint();


        //input -= ui->tabWidget_2->count();
        qDebug() << "tab widget size " << ui->SupportTabWidget->count();
        if(input.size() > (uint)ui->SupportTabWidget->count())
        {
            for(uint i = (ui->SupportTabWidget->count()); i < input.size(); i++)
            {
                qDebug() << i;
                _attorneyAndSupportVector.push_back(new AttorneyAndSupportForMediationSessionView());
                ui->SupportTabWidget->addTab(_attorneyAndSupportVector.at(i),QString::fromStdString("Party " + std::to_string(ui->SupportTabWidget->count() + 1)));
            }
        }
        else
        {
            for(int i = input.size();i < ui->SupportTabWidget->count(); i++)
                ui->SupportTabWidget->removeTab(ui->SupportTabWidget->count()-1);
        }

    qDebug() << "input size: " << input.size();
    qDebug() << "attorney Vector size: " << _attorneyAndSupportVector.size();
    if(input.size() == _attorneyAndSupportVector.size())
    {
        for(uint i = 0; i < _attorneyAndSupportVector.size(); i++)
        {
            qDebug() << i;
            qDebug() << QString::fromStdString(input.at(i)->getAttorney());
            _attorneyAndSupportVector.at(i)->setAttorney(QString::fromStdString(input.at(i)->getAttorney()));
        }
    }
}

void MediationSession::on_CancelledRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _localMediationSessionClassVector[sessionCurrentRow].setCancelledRB(checked);
        PopulateSessionTable();
    }
}

void MediationSession::on_PendingRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _localMediationSessionClassVector[sessionCurrentRow].setPendingRB(checked);
        PopulateSessionTable();
    }
}

void MediationSession::on_confirmedRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _localMediationSessionClassVector[sessionCurrentRow].setConfirmedRB(checked);
        PopulateSessionTable();
    }
}

void MediationSession::on_rescheduledRadioButton_toggled(bool checked)
{
    if(!FillingFields)
    {
        _localMediationSessionClassVector[sessionCurrentRow].setRescheduledRB(checked);
        PopulateSessionTable();
    }
}

void MediationSession::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(!FillingFields)
    {
        _localMediationSessionClassVector[sessionCurrentRow].setMediationTime(dateTime);
        PopulateSessionTable();
    }
}

void MediationSession::on_Fee1LineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFee1(ui->Fee1LineEdit->text());
}

void MediationSession::on_Fee1PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFee1Paid(checked);
}

void MediationSession::configSessionTable()
{
    _sessionTable = ui->sessiontTableWidget;
    _sessionTable->setColumnCount(3);
    _sessionTable->setRowCount(_localMediationSessionClassVector.size() + 1);
    _sessionTableHeader <<"Date Time"<<" "<<"Status";
    _sessionTable->setHorizontalHeaderLabels(_sessionTableHeader);
    _sessionTable->verticalHeader()->setVisible(false);
    _sessionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _sessionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _sessionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _sessionTable->setShowGrid(true);
    _sessionTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _sessionTable->horizontalHeader()->count(); ++c)
    {
        _sessionTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}
void MediationSession::PopulateSessionTable()
{
    int row;
    for(row=0; row < (int)_localMediationSessionClassVector.size(); ++row)
    {
        //insert data
        MediationSessionClass o = _localMediationSessionClassVector[row];

        _sessionTable->setItem(row, 0, new QTableWidgetItem(o.getMediationTime().toString()));

        _sessionTable->setItem(row, 2, new QTableWidgetItem(o.getStatus()));

    }
    _sessionTable->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session."));
    //ui->sessiontTableWidget->setCurrentCell(0,0);
}

void MediationSession::on_sessiontTableWidget_itemSelectionChanged()
{

    if(sessionCurrentRow != ui->sessiontTableWidget->currentRow())
    {
        sessionCurrentRow = ui->sessiontTableWidget->currentRow();

        if((uint)sessionCurrentRow<_localMediationSessionClassVector.size())
            fillFields(_localMediationSessionClassVector[sessionCurrentRow]);
    }

}

void MediationSession::fillFields(MediationSessionClass input)
{
    FillingFields = true;
    ui->CancelledRadioButton->setChecked(input.getCancelledRB());
    ui->confirmedRadioButton->setChecked(input.getConfirmedRB());
    ui->dateTimeEdit->setDateTime(input.getMediationTime());
    ui->dateTimeEdit->setVisible(true);
    ui->FamilyFeeLineEdit->setText(input.getFeeFamily());
    ui->FamilyFeePaidCheckBox->setChecked(input.getFeeFamilyPaid());
    ui->Fee1LineEdit->setText(input.getFee1());
    ui->Fee2LineEdit->setText(input.getFee2());
    ui->OtherFeeLineEdit->setText(input.getFeeOther());
    ui->Fee1PaidCheckBox->setChecked(input.getFee1Paid());
    ui->Fee2PaidCheckBox->setChecked(input.getFee2Paid());
    ui->OtherFeePaidCheckBox->setChecked(input.getFeeOtherPaid());
    ui->incomeFee1LineEdit->setText(input.getIncomeFee1());
    ui->incomeFee2LineEdit->setText(input.getIncomeFee2());
    ui->incomeFeeFamilyLineEdit->setText(input.getIncomeFeeFamily());
    ui->incomeFeeOtherLineEdit->setText(input.getIncomeFeeOther());
    if(input.getMediator1()!=NULL)
        ui->Mediator2LineEdit->setText(input.getMediator2()->FullName());
    if(input.getMediator2()!=NULL)
        ui->MediatorLineEdit->setText(input.getMediator1()->FullName());
    ui->PendingRadioButton->setChecked(input.getPendingRB());
    ui->rescheduledRadioButton->setChecked(input.getRescheduledRB());
    if(input.getObserver1()!=NULL)
        ui->Observe1LineEdit->setText(input.getObserver1()->FullName());
    if(input.getObserver2()!=NULL)
        ui->Observer2lineEdit->setText(input.getObserver2()->FullName());
    FillingFields = false;
}

void MediationSession::on_sessiontTableWidget_doubleClicked(const QModelIndex &index)
{
    MediationSessionClass temp;
   _localMediationSessionClassVector.push_back(temp);
   configSessionTable();
   PopulateSessionTable();
   ui->sessiontTableWidget->setCurrentCell(_localMediationSessionClassVector.size()-1,0);
   fillFields(_localMediationSessionClassVector[_localMediationSessionClassVector.size() - 1]);

}

void MediationSession::on_Fee2LineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFee2(ui->Fee2LineEdit->text());
}

void MediationSession::on_FamilyFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFeeFamily(ui->FamilyFeeLineEdit->text());
}

void MediationSession::on_OtherFeeLineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFeeOther(ui->OtherFeeLineEdit->text());
}

void MediationSession::on_Fee2PaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFee2Paid(checked);
}

void MediationSession::on_FamilyFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFeeFamilyPaid(checked);
}

void MediationSession::on_OtherFeePaidCheckBox_toggled(bool checked)
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setFeeOtherPaid(checked);
}

void MediationSession::on_incomeFee1LineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setIncomeFee1(ui->incomeFee1LineEdit->text());
}

void MediationSession::on_incomeFee2LineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setIncomeFee2(ui->incomeFee2LineEdit->text());
}

void MediationSession::on_incomeFeeFamilyLineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setIncomeFeeFamily(ui->incomeFeeFamilyLineEdit->text());
}

void MediationSession::on_incomeFeeOtherLineEdit_editingFinished()
{
    if(!FillingFields)
        _localMediationSessionClassVector[sessionCurrentRow].setIncomeFeeOther(ui->incomeFeeOtherLineEdit->text());
}

void MediationSession::on_mediator1EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_localMediationSessionClassVector[sessionCurrentRow].getMediator1(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;

}

void MediationSession::on_mediator2EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(this,_localMediationSessionClassVector[sessionCurrentRow].getMediator2(),true);
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
}

void MediationSession::on_observer1EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(0,_localMediationSessionClassVector[sessionCurrentRow].getObserver1());
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
}

void MediationSession::on_observer2EditPushButton_clicked()
{
    PersonDetailsForm *popup = new PersonDetailsForm(0,_localMediationSessionClassVector[sessionCurrentRow].getObserver2());
    popup->setWindowFlags(Qt::Popup);
    popup->SetEditMode(true);
    connect(popup,SIGNAL(PersonDeleted(Person*)),this,SLOT(deletePersonContact(Person*)));
    connect(popup,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContact(Person*)));
    popup->show();
    //delete popup;
}

void MediationSession::savePersonContact(Person *value)
{
    if(value)
        fillFields(_localMediationSessionClassVector[sessionCurrentRow]);
}

void MediationSession::deletePersonContact(Person *value)
{
    if(value)
        fillFields(_localMediationSessionClassVector[sessionCurrentRow]);
}
