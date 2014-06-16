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

    _mediationProcessVector = new MediationProcessVector();
    // TEMP SAMPLE DATA
    for(int i = 0; i < 7; i++)
        _mediationProcessVector->push_back(MediationProcess::SampleData());

    // Recent records table
    _mediationProcessTableView = ui->MediationProcessTableWidget;
    _mediationProcessTableView->setMaximumHeight(200);
    configMediationProcecssViewTable();
    PopulateMediationProcessTable();
    _currentProcessRow= 1;

    _mediationProcessStatusForm = new MediationProcessStatusForm(this, _mediationProcess);
    _partiesContainerForm = new PartiesContainerForm(this, &_mediationProcess->GetParties());
    _mediationSessionForm = new MediationSessionForm(this);

    ConfigureToolbox();

    // Update Fields for current record
    PopulateView(_mediationProcessVector->at(_currentProcessRow-1));

    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::ConfigureToolbox()
{
    _toolBox = ui->MediationProcessToolBox;
    ui->MediationProcessToolBox->removeItem(0);
    _toolBox->addItem(_mediationProcessStatusForm, "Mediation Overview");
    _toolBox->addItem(_partiesContainerForm, "Parties");
    _toolBox->addItem(_mediationSessionForm,"Mediation Sessions");

    foreach(QWidget* child, _toolBox->findChildren<QWidget*>())
        if( child->inherits("QToolBoxButton") )
            child->setFont(QFont("Helvetica", 28, 5));
}

void MediationProcessView::savePersonContactFromFarAway(Person *value)
{
    PopulateView(_mediationProcessVector->at(_currentProcessRow-1));
    PopulateMediationProcessTable();
}

void MediationProcessView::PopulateView(MediationProcess *value)
{
    _mediationProcessStatusForm->setMediationProcess(value);
    _mediationSessionForm->setMediationSessionVector(value->getMediationSessionVector());
    _partiesContainerForm->AddPartyTabs(&value->GetParties());
    connect(_partiesContainerForm,SIGNAL(PassItOnAgain(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));
}

void MediationProcessView::configMediationProcecssViewTable()
{
        //_mediationProcessTableView = ui->sessiontTableWidget;
        _mediationProcessTableView->setColumnCount(3);
        _mediationProcessTableView->setRowCount(11);
        _mediationProcessTableViewHeader <<"Date Time"<<" "<<"Status";
        _mediationProcessTableView->setHorizontalHeaderLabels(_mediationProcessTableViewHeader);
        _mediationProcessTableView->verticalHeader()->setVisible(false);
        _mediationProcessTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        _mediationProcessTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        _mediationProcessTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        _mediationProcessTableView->setShowGrid(true);
        _mediationProcessTableView->setStyleSheet("QTableView {selection-background-color: red;}");

        for (int c = 0; c < _mediationProcessTableView->horizontalHeader()->count(); ++c)
        {
            _mediationProcessTableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }
}
void MediationProcessView::PopulateMediationProcessTable()
{
    int row=0;
     _mediationProcessTableView->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    for(row=1; row < (int)_mediationProcessVector->size()+1; ++row)
    {
        //insert data
        MediationProcess *o = _mediationProcessVector->at(row-1);
        _mediationProcessTableView->setItem(row, 0, new QTableWidgetItem(o->GetCreationDate().toString()));
        _mediationProcessTableView->setItem(row, 1, new QTableWidgetItem(o->GetPartyAtIndex(0)->GetPrimary()->FullName()));
        _mediationProcessTableView->setItem(row, 2, new QTableWidgetItem(o->GetCurrentState()));

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

        if((uint)_currentProcessRow < _mediationProcessVector->size() && _currentProcessRow > 0)
            PopulateView(_mediationProcessVector->at(_currentProcessRow-1));
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
        _mediationProcessVector->insert(_mediationProcessVector->begin(),new MediationProcess());
        ui->MediationProcessTableWidget->setCurrentCell(1,0);
        _currentProcessRow = 1;
        PopulateMediationProcessTable();
        PopulateView(_mediationProcessVector->at(_currentProcessRow-1));
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

