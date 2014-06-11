#include "mediationsession.h"
#include "ui_mediationsession.h"
#include <QDebug>

MediationSession::MediationSession(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationSession)
{
    ui->setupUi(this);
    ui->dateTimeEdit->clear();
    for(int i = 0; i < 3; i++)
    {
        MediationSessionClass a;
        a = a.SampleData();
        _localMediationSessionClassVector.push_back(a);
    }
    configSessionTable();
    PopulateSessionTable();

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
    //_localMediationSessionClass.setCancelledRB(checked);
}

void MediationSession::on_PendingRadioButton_toggled(bool checked)
{
   // _localMediationSessionClass.setPendingRB(checked);
}

void MediationSession::on_confirmedRadioButton_toggled(bool checked)
{
   // _localMediationSessionClass.setConfirmedRB(checked);
}

void MediationSession::on_rescheduledRadioButton_toggled(bool checked)
{
   // _localMediationSessionClass.setRescheduledRB(checked);
}

void MediationSession::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
   // _localMediationSessionClass.setMediationTime(dateTime);
}

void MediationSession::on_Fee1LineEdit_editingFinished()
{
    //_localMediationSessionClass.setFee1(ui->Fee1LineEdit->text());
}

void MediationSession::on_Fee1PaidCheckBox_toggled(bool checked)
{
    //_localMediationSessionClass.setFee1Paid(checked);
}

void MediationSession::configSessionTable()
{
    _sessionTable = ui->sessiontTableWidget;
    _sessionTable->setColumnCount(3);
    _sessionTable->setRowCount(5);
    _sessionTableHeader <<"Date Time"<<"Name"<<"Status";
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
}
