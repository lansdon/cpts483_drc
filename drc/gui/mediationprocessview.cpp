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




MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess *mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

//    ui->clientSessionsContainer->
    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);
    _sessionOverview = new SessionOverview(ui->sessionOverviewContainer, _mediationProcess->getMediationSessionVector());

//    _partiesContainerForm = new PartiesContainerForm(this, &_mediationProcess->GetParties());
//    _mediationSessionForm = new MediationSessionForm(this);

    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);



//    connect(_mediationProcessStatusForm,SIGNAL(hovered()),this, SLOT(onHovered()));

    // Set the parties container
//    QVBoxLayout* pLayout = new QVBoxLayout();
//    pLayout->addWidget(_partiesContainerForm);
//    ui->clientsContainer->setLayout(pLayout);

    // Set the sessions container
//    QVBoxLayout* sLayout = new QVBoxLayout();
//    sLayout->addWidget(_mediationSessionForm);
//    ui->sessionsContainer->setLayout(sLayout);

    configSessionTable();

    // Update Fields for current record
    PopulateView(_mediationProcess);

    // Each View can setup it's own toolbar buttons
    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

//void MediationProcessView::savePersonContactFromFarAway(Person *value)
//{
//    PopulateView(_mediationProcess);
//}

void MediationProcessView::PopulateView(MediationProcess *process)
{
    _mediationProcess = process;
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();

    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
//    _mediationSessionForm->setMediationSessionVector(_mediationProcess->getMediationSessionVector());
//    _partiesContainerForm->AddPartyTabs(&_mediationProcess->GetParties());
//    connect(_partiesContainerForm,SIGNAL(PassItOnAgain(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));

    AddPartyTabs(&_mediationProcess->GetParties());

    PopulateSessionTable();
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));
    toolbar.AddAction("Show Recent Records", this, SLOT(ShowRecentPressed()));
}

void MediationProcessView::SaveMediationPressed()
{
    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";

}

void MediationProcessView::SearchForMediationPressed()
{
    qDebug() << "SEARCH MEDIATION PRESSED - Toolbar manager.";
}

void MediationProcessView::ShowRecentPressed()
{
    Mediator::Call(MKEY_GUI_TOGGLE_MEDIATION_TABLE_DOCK);
}

void MediationProcessView::SetMediationProcess(MediationProcess* process)
{
    _mediationProcess = process;
    PopulateView(_mediationProcess);
}


void MediationProcessView::configSessionTable()
{
    _sessionTable = ui->sessionsTable;
    _sessionTable->setColumnCount(1);
    _sessionTable->setRowCount(_mediationProcess->getMediationSessionVector()->size() + 1);
//    QStringList _sessionTableHeader <<"Mediation Sessions";
    _sessionTable->setHorizontalHeaderLabels({"Mediation Sessions"});
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

void MediationProcessView::PopulateSessionTable()
{
    _sessionTable->clearContents();

    MediationSessionVector* sessionsVec = _mediationProcess->getMediationSessionVector();
    int row;
    for(row=0; row < (int)sessionsVec->size(); ++row)
    {
        MediationSessionForm* sessionForm = new MediationSessionForm(_sessionTable, sessionsVec->at(row));
        _sessionTable->insertRow(row);
        _sessionTable->setRowHeight(row, 100);
        _sessionTable->setCellWidget(row, 0, sessionForm);
 //       _sessionTable->setItem(row, 0, new MediationSessionForm(_sessionTable, session));
    }
    _sessionTable->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    ui->sessionsTable->setCurrentCell(0,0);
}

void MediationProcessView::on_sessiontTableWidget_itemSelectionChanged()
{

//    if(sessionCurrentRow != ui->sessiontTableWidget->currentRow())
//    {
//        sessionCurrentRow = ui->sessiontTableWidget->currentRow();

//        if((uint)sessionCurrentRow<_mediationSessions->size())
//            fillFields(_mediationSessions->at(sessionCurrentRow));
//    }

}


void MediationProcessView::AddPartyTabs(PartyVector* parties)
{
    if(parties)
    {
        ui->partyTabWidget->clear();
        foreach(Party* party, *parties)
        {
            if(party)
            {
                PartyForm* pForm = new PartyForm(ui->partyTabWidget, party);
                ui->partyTabWidget->addTab(pForm, party->GetPrimary()->FullName() );
                connect(pForm,SIGNAL(SaveSignaled()),this,SLOT(SaveSignaled()));
            }
        }
//        foreach(PartyForm* p, PartyFormVector)
//        {
//            ui->partyTabWidget->addTab(p, p->getFullName() );
//            connect(p,SIGNAL(PassItOn(Person*)),this,SLOT(savePersonContactFromFar(Person*)));
//        }
    }
}
