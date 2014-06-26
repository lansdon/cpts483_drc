#include "mediationbrowser.h"
#include "ui_mediationbrowser.h"
#include "DRCModels.h"
#include <QDebug>

MediationBrowser::MediationBrowser(QWidget *parent, MediationTableSortTypes sortType) :
    QWidget(parent),
    ui(new Ui::MediationBrowser)
{
    ui->setupUi(this);
    ConfigMediationProcecssViewTable();
    LoadTableData(sortType);
}

MediationBrowser::~MediationBrowser()
{
    delete ui;
}


void MediationBrowser::ConfigMediationProcecssViewTable()
{
        //ui->tableWidget = ui->sessiontTableWidget;
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setRowCount(_mediationsVector.size());
        QStringList header;
        header <<"Date Time"<<"Party1"<<"Status";
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");

        for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
        {
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }
}
void MediationBrowser::PopulateMediationProcessTable()
{
    ui->tableWidget->setRowCount(_mediationsVector.size());

    for(int row=0; row < (int)_mediationsVector.size(); ++row)
    {
        qDebug() << "populate row: " << row;
        //insert data
        MediationProcess *o = _mediationsVector.at(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(o->GetCreationDate().toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(o->GetPartyAtIndex(0)->GetPrimary()->FullName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(StringForDisputeProcessStates( o->GetCurrentState())));
    }
}

void MediationBrowser::on_recentButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_RECENT);
}

void MediationBrowser::on_pendingButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_PENDING);
}

void MediationBrowser::on_scheduledButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_SCHEDULED);
}

void MediationBrowser::on_closedButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_CLOSED);
}

void MediationBrowser::LoadTableData(MediationTableSortTypes sortType)
{
    // TO DO - Setup database query!!
    MakeSampleTable();

    PopulateMediationProcessTable();
}

void MediationBrowser::MakeSampleTable()
{

//    _mediationsVector.clear();
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
}

void MediationBrowser::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() << "on_tableWidget_doubleClicked row=" << index.row();
    if(index.row() >= 0 && index.row() < _mediationsVector.size())

    emit on_mediationProcessSelected(_mediationsVector.at(index.row()));

}

