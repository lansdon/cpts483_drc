#include "mediationbrowser.h"
#include "ui_mediationbrowser.h"
#include "DRCModels.h"
#include <QDebug>
#include "Mediator.h"
#include "MediatorKeys.h"
#include "drctypes.h"

MediationBrowser::MediationBrowser(QWidget *parent, MediationTableSortTypes sortType) :
    QWidget(parent),
    ui(new Ui::MediationBrowser)
{
    ui->setupUi(this);

    ConfigMediationProcecssViewTable();

    _requestRecentCallback = Mediator::Register(MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE, [this](MediatorArg arg){OnRecieveMediationVector(arg);});
    _setMediationsCallback = Mediator::Register(MKEY_DOCK_SET_MEDIATIONS, [this](MediatorArg arg){OnRecieveMediationVector(arg);});
    _refreshMediationsCallback = Mediator::Register(MKEY_DOCK_REFRESH_MEDIATIONS, [this](MediatorArg arg){Q_UNUSED(arg);LoadTableData(_sortType);});
    _queryMediationCallback = Mediator::Register(MKEY_DB_QUERY_MEDIATION, [this](MediatorArg arg){OnRecieveMediationVector(arg);});

    LoadTableData(sortType);

}

MediationBrowser::~MediationBrowser()
{
    Mediator::Unregister(MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE, _requestRecentCallback);
    Mediator::Unregister(MKEY_DOCK_SET_MEDIATIONS, _setMediationsCallback);
    Mediator::Unregister(MKEY_DOCK_REFRESH_MEDIATIONS, _refreshMediationsCallback);
    Mediator::Unregister(MKEY_DB_QUERY_MEDIATION, _queryMediationCallback);

    delete ui;
}

void MediationBrowser::Refresh()
{
    LoadTableData(_sortType);
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
        //insert data
        MediationProcess *mp = _mediationsVector.at(row);
        if(mp)
        {
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(mp->GetUpdatedDate().toString("MM/dd/yyyy")));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(mp->GetParties()->size() ? mp->GetPartyAtIndex(0)->GetPrimary()->FullName() : "N/A"));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(StringForDisputeProcessStates( mp->GetState())));
        }
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
    _sortType = sortType;

    if(sortType == MEDIATION_SORT_T_RECENT)
        Mediator::Call(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS);
    else
        //MakeSampleTable();

    switch(sortType)
    {
        case MEDIATION_SORT_T_RECENT:
        {
            Mediator::Call(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS);
            break;
        }
        case MEDIATION_SORT_T_PENDING:
        {
            Mediator::Call(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS);
            break;
        }
        case MEDIATION_SORT_T_SCHEDULED:
        {
            Mediator::Call(MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS);
            break;
        }
        case MEDIATION_SORT_T_CLOSED:
        {
            Mediator::Call(MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS);
            break;
        }
        default:
        {
            MakeSampleTable();
            break;
        }
    }
    PopulateMediationProcessTable();
}

void MediationBrowser::OnRecieveMediationVector( MediatorArg arg)
{
    MediationProcessVector* mediations = arg.getArg<MediationProcessVector*>();
    if(mediations)
    {
        _mediationsVector = *mediations;
        PopulateMediationProcessTable();
    }
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
    if(index.row() >= 0 && index.row() < (int)_mediationsVector.size())
        emit on_mediationProcessSelected(_mediationsVector.at(index.row()));
}


void MediationBrowser::on_searchBtn_clicked()
{
    // Using a person object to hold the search variables.
    Person* searchParams = new Person();
    searchParams->setFirstName(ui->firstnameLineEdit->text());
    searchParams->setLastName(ui->lastnameLineEdit->text());

    Mediator::Call(MKEY_GUI_QUERY_MEDIATION, searchParams);
}
