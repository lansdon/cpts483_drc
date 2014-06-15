#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"
#include <QWidget>
#include <QListWidget>
#include "mediationprocess.h"
#include "partiescontainerform.h"
#include "party.h"
#include <QToolBox>

#include "mediationprocessstatusform.h"
#include <QDebug>
#include "toolbarmanager.h"



MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    _localMediationProcessVector = new MediationProcessVector();
    // TEMP SAMPLE DATA
    for(int i = 0; i < 7; i++)
        _localMediationProcessVector->push_back(MediationProcess::SampleData());

    // Recent records table
    MediationProcessTableView = ui->MediationProcessTableWidget;
    MediationProcessTableView->setMaximumHeight(200);
    configMediationProcecssViewTable();
    PopulateMediationProcessTable();
    _currentProcessRow= 1;

    _localMediationProcessStatusForm = new MediationProcessStatusForm(this, _mediationProcess);
    _localPartiesContainerForm = new PartiesContainerForm(this, &_mediationProcess->GetParties());
    _localMediationSession = new MediationSession(this);

    ConfigureToolbox();

    // Update Fields for current record
    PopulateView(_localMediationProcessVector->at(_currentProcessRow-1));

    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::ConfigureToolbox()
{
    toolBox = ui->MediationProcessToolBox;
    ui->MediationProcessToolBox->removeItem(0);
    toolBox->addItem(_localMediationProcessStatusForm, "Mediation Overview");
    toolBox->addItem(_localPartiesContainerForm, "Parties");
    toolBox->addItem(_localMediationSession,"Mediation Sessions");

    foreach(QWidget* child, toolBox->findChildren<QWidget*>())
        if( child->inherits("QToolBoxButton") )
            child->setFont(QFont("Helvetica", 28, 5));
}

void MediationProcessView::savePersonContactFromFarAway(Person *value)
{
    PopulateView(_localMediationProcessVector->at(_currentProcessRow-1));
    PopulateMediationProcessTable();
}

void MediationProcessView::PopulateView(MediationProcess *value)
{
    _localMediationProcessStatusForm->setMediationProcess(value);
    _localMediationSession->setMediationSessionClassVector(value->getMediationSessionVector());
    _localPartiesContainerForm->AddPartyTabs(&value->GetParties());
    connect(_localPartiesContainerForm,SIGNAL(PassItOnAgain(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));
}

void MediationProcessView::configMediationProcecssViewTable()
{
        //MediationProcessTableView = ui->sessiontTableWidget;
        MediationProcessTableView->setColumnCount(3);
        MediationProcessTableView->setRowCount(11);
        MediationProcessTableViewHeader <<"Date Time"<<" "<<"Status";
        MediationProcessTableView->setHorizontalHeaderLabels(MediationProcessTableViewHeader);
        MediationProcessTableView->verticalHeader()->setVisible(false);
        MediationProcessTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        MediationProcessTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        MediationProcessTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        MediationProcessTableView->setShowGrid(true);
        MediationProcessTableView->setStyleSheet("QTableView {selection-background-color: red;}");

        for (int c = 0; c < MediationProcessTableView->horizontalHeader()->count(); ++c)
        {
            MediationProcessTableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }
}
void MediationProcessView::PopulateMediationProcessTable()
{
    int row=0;
     MediationProcessTableView->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    for(row=1; row < (int)_localMediationProcessVector->size()+1; ++row)
    {
        //insert data
        MediationProcess *o = _localMediationProcessVector->at(row-1);
        MediationProcessTableView->setItem(row, 0, new QTableWidgetItem(o->GetCreationDate().toString()));
        MediationProcessTableView->setItem(row, 1, new QTableWidgetItem(o->GetPartyAtIndex(0)->GetPrimary()->FullName()));
        MediationProcessTableView->setItem(row, 2, new QTableWidgetItem(o->GetCurrentState()));

    }
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));
    toolbar.AddAction("Show Recent Records", this, SLOT(ShowRecentPressed()));
}



void MediationProcessView::on_MediationProcessTableWidget_itemSelectionChanged()
{
    if(_currentProcessRow != ui->MediationProcessTableWidget->currentRow())
    {
        _currentProcessRow = ui->MediationProcessTableWidget->currentRow();

        if((uint)_currentProcessRow < _localMediationProcessVector->size() && _currentProcessRow > 0)
            PopulateView(_localMediationProcessVector->at(_currentProcessRow-1));
    }
}

void MediationProcessView::SaveMediationPressed()
{
    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";

}

void MediationProcessView::SearchForMediationPressed()
{
    qDebug() << "SEARCH MEDIATION PRESSED - Toolbar manager.";

}

void MediationProcessView::on_MediationProcessTableWidget_doubleClicked(const QModelIndex &index)
{
    if(index.row() == 0)
    {
        _localMediationProcessVector->insert(_localMediationProcessVector->begin(),new MediationProcess());
        ui->MediationProcessTableWidget->setCurrentCell(1,0);
        _currentProcessRow = 1;
        PopulateMediationProcessTable();
        PopulateView(_localMediationProcessVector->at(_currentProcessRow-1));
        //PersonDetailsForm *child = _localPartiesContainerForm->findChild<PersonDetailsForm *>();
        //connect(child,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));
    }
}

void MediationProcessView::ShowRecentPressed()
{
    if(ui->recentGroupBox->isVisible())
        ui->recentGroupBox->hide();
    else
        ui->recentGroupBox->show();
}

