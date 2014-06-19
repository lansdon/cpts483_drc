#include "mediationprocesstableform.h"
#include "ui_mediationprocesstableform.h"
#include "DRCModels.h"
#include <QDebug>

MediationProcessTableForm::MediationProcessTableForm(QWidget *parent, MediationTableSortTypes sortType) :
    QWidget(parent),
    ui(new Ui::MediationProcessTableForm)
{
    ui->setupUi(this);

//    LoadTableData(sortType);
}

MediationProcessTableForm::~MediationProcessTableForm()
{
    delete ui;
}


void MediationProcessTableForm::ConfigMediationProcecssViewTable()
{
        //ui->tableWidget = ui->sessiontTableWidget;
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setRowCount(11);
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
void MediationProcessTableForm::PopulateMediationProcessTable()
{
    for(int row=0; row < (int)_mediationsVector.size(); ++row)
    {
        qDebug() << "populate row: " << row;
        //insert data
        MediationProcess *o = _mediationsVector.at(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(o->GetCreationDate().toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(o->GetPartyAtIndex(0)->GetPrimary()->FullName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(o->GetCurrentState()));
    }
}

void MediationProcessTableForm::on_recentButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_RECENT);
}

void MediationProcessTableForm::on_pendingButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_PENDING);
}

void MediationProcessTableForm::on_scheduledButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_SCHEDULED);
}

void MediationProcessTableForm::on_closedButton_clicked()
{
    LoadTableData(MEDIATION_SORT_T_CLOSED);
}

void MediationProcessTableForm::LoadTableData(MediationTableSortTypes sortType)
{
    // TO DO - Setup database query!!
    MakeSampleTable();

    PopulateMediationProcessTable();
}

void MediationProcessTableForm::MakeSampleTable()
{
    _mediationsVector.clear();
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
    _mediationsVector.push_back(MediationProcess::SampleData());
}
