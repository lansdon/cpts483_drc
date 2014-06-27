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
    _noSession = new NoSessionsView(ui->sessionOverviewGroupBox);
    // Set the No session container
    QVBoxLayout* layout3 = new QVBoxLayout();
    layout2->addWidget(_noSession);
    ui->sessionOverviewGroupBox->setLayout(layout3);

    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);
    connect(_noSession,SIGNAL(sendAddNewSession()),this,SLOT(addSession()));
    // Update Fields for current record
    PopulateView();

}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::PopulateView()
{
//    _mediationProcess = process;
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();

    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);

    // PARTY!
    AddPartyTabs(_mediationProcess->GetParties());

    // DOCK Sesssions
    Mediator::Call(MKEY_DOCK_SET_SESSIONS, _mediationProcess->getMediationSessionVector());
    // DOCK Notes
    Mediator::Call(MKEY_DOCK_SET_NOTES, _mediationProcess->GetNotes());

    // Session detail.
    if(_mediationProcess->getMediationSessionVector()->size() > 0 )
    {
        _noSession->hide();
         _mediationSessionForm->setMediationSession(_mediationProcess->getMediationSessionVector()->at(0));
        _mediationSessionForm->show();
    }
    else
    {
        _mediationSessionForm->hide();
        _noSession->show();
    }


    // Each View can setup it's own toolbar buttons
    ConfigureToolbar();
}
void MediationProcessView::addSession()
{
    _mediationProcess->addMediation();
    PopulateView();
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Mediation Browser", this, SLOT(ShowMediationBrowserPressed()));
    toolbar.AddAction("Session Browser", this, SLOT(ShowSessionBrowserPressed()));
    toolbar.AddAction("Notes Browser", this, SLOT(ShowNotesBrowserPressed()));
}

void MediationProcessView::SaveMediationPressed()
{
    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";
    Mediator::Call(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _mediationProcess);
}

void MediationProcessView::SearchForMediationPressed()
{
    qDebug() << "SEARCH MEDIATION PRESSED - Toolbar manager.";
}

void MediationProcessView::ShowMediationBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_MEDIATION_BROWSER);
}

void MediationProcessView::ShowNotesBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_NOTES_BROWSER);
}

void MediationProcessView::ShowSessionBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_SESSIONS_BROWSER);
}

void MediationProcessView::SetMediationProcess(MediationProcess* process)
{
    _mediationProcess = process;
    PopulateView();
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
    }
}

void MediationProcessView::on_addCientPushButton_clicked()
{
    _mediationProcess->AddParty(new Party());
    PopulateView();
}

void MediationProcessView::on_removeClientPushButton_clicked()
{
    _mediationProcess->removeParty(ui->partyTabWidget->currentIndex());
    PopulateView();
}
