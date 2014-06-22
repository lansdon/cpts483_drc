#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"

// QT
#include <QWidget>
#include <QListWidget>
#include <QToolBox>
#include <QDebug>

// DRC
#include "mediationprocessstatusform.h"
#include "toolbarmanager.h"
#include "DRCModels.h"
#include "partiescontainerform.h"
#include "MediatorKeys.h"




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
    //_mediationProcessTableView = ui->MediationProcessTableWidget;
    _mediationProcessTableView = new QTableWidget();
    _mediationProcessTableView->setMaximumHeight(200);
    _mediationProcessTableView->setMaximumWidth(400);
    configMediationProcecssViewTable();
    PopulateMediationProcessTable();
    _currentProcessRow= 1;
//    ui->recentGroupBox->setMinimumHeight(500);
//    ui->MediationOverviewWidget->setMinimumHeight(400);
    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);
    _partiesContainerForm = new PartiesContainerForm(this, &_mediationProcess->GetParties());
    _mediationSessionForm = new MediationSessionForm(this);

    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);
    connect(_mediationProcessStatusForm,SIGNAL(hovered()),this, SLOT(onHovered()));
    ConfigureToolbox();

    // Update Fields for current record
    PopulateView(_mediationProcessVector->at(_currentProcessRow-1));

    ConfigureToolbar();
}
void MediationProcessView::onHovered()
{

   _mediationProcessTableView->setParent(this);
    _mediationProcessTableView->show();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::ConfigureToolbox()
{
    _toolBox = ui->MediationProcessToolBox;
    ui->MediationProcessToolBox->removeItem(0);
    //_toolBox->addItem(_mediationProcessStatusForm, "Mediation Overview");
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
    if(_currentProcessRow != _mediationProcessTableView->currentRow())
    {
        _currentProcessRow = _mediationProcessTableView->currentRow();

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
        _mediationProcessTableView->setCurrentCell(1,0);
        _currentProcessRow = 1;
        PopulateMediationProcessTable();
        PopulateView(_mediationProcessVector->at(_currentProcessRow-1));
        //PersonDetailsForm *child = _localPartiesContainerForm->findChild<PersonDetailsForm *>();
        //connect(child,SIGNAL(PersonSaved(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));
    }
}

void MediationProcessView::ShowRecentPressed()
{
    Mediator::Call(MKEY_GUI_TOGGLE_MEDIATION_TABLE_DOCK);
}

