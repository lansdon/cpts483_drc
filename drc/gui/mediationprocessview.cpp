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
#include "nosessionsview.h"




MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess *mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);


        _mediationSessionForm = new MediationSessionForm(ui->sessionOverviewGroupBox);
        // Set the session container
        QVBoxLayout* layout2 = new QVBoxLayout();
        layout2->addWidget(_mediationSessionForm);
        ui->sessionOverviewGroupBox->setLayout(layout2);
        _mediationSessionForm->hide();
        _noSession = new NoSessionsView(ui->sessionOverviewGroupBox);
        // Set the No session container
        QVBoxLayout* layout3 = new QVBoxLayout();
        layout2->addWidget(_noSession);
        ui->sessionOverviewGroupBox->setLayout(layout3);


    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);



//    configSessionTable();
    ui->sessionsContainer->hide();

    // Update Fields for current record
    PopulateView(_mediationProcess);

    // Each View can setup it's own toolbar buttons
    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::PopulateView(MediationProcess *process)
{
    _mediationProcess = process;
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();

    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
//    _mediationSessionForm->setMediationSessionVector(_mediationProcess->getMediationSessionVector());
//    _partiesContainerForm->AddPartyTabs(&_mediationProcess->GetParties());
//    connect(_partiesContainerForm,SIGNAL(PassItOnAgain(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));

    // PARTY!
    AddPartyTabs(&_mediationProcess->GetParties());


//    PopulateSessionTable();

    // DOCK Sesssions
    Mediator::Call(MKEY_DOCK_SET_SESSIONS, _mediationProcess->getMediationSessionVector());

    // Session detail.
    if(_mediationProcess->getMediationSessionVector()->size() > 0 )
    {
        if(_noSession->isVisible())
        {
            _noSession->hide();
            //_mediationSessionForm = new MediationSessionForm(ui->sessionOverviewGroupBox, _mediationProcess->getMediationSessionVector()->at(0));
            // Set the session container
//            QVBoxLayout* layout2 = new QVBoxLayout();
//            layout2->addWidget(_mediationSessionForm);
//            ui->sessionOverviewGroupBox->setLayout(layout2);
//            ui->sessionOverviewGroupBox->repaint();
            _mediationSessionForm->setMediationSession(_mediationProcess->getMediationSessionVector()->at(0));
            _mediationSessionForm->show();
//            delete _noSession;
//            _noSession = nullptr;
        }
        else
            _mediationSessionForm->setMediationSession(_mediationProcess->getMediationSessionVector()->at(0));
    }
    else
    {
        _mediationSessionForm->hide();
        _noSession->show();
    }
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));
    toolbar.AddAction("Mediation Browser", this, SLOT(ShowRecentPressed()));
    toolbar.AddAction("Session Browser", this, SLOT(ShowSessionBrowserPressed()));
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
    Mediator::Call(MKEY_GUI_SHOW_MEDIATION_BROWSER);
}


void MediationProcessView::ShowSessionBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_SESSIONS_BROWSER);
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
