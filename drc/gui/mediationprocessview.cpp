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
#include "MediatorKeys.h"
#include "nosessionsview.h"
#include "partyform.h"

MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess *mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);

    //_mediationSessionForm = new MediationSessionForm(ui->sessionOverviewGroupBox);

//    // Set the session container
//    QVBoxLayout* layout2 = new QVBoxLayout();
//    layout2->addWidget(_mediationSessionForm);
//    ui->sessionOverviewGroupBox->setLayout(layout2);
//    _noSession = new NoSessionsView(ui->sessionOverviewGroupBox);
//    // Set the No session container
//    QVBoxLayout* layout3 = new QVBoxLayout();
//    layout2->addWidget(_noSession);
//    ui->sessionOverviewGroupBox->setLayout(layout3);

    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);
//    connect(_noSession,SIGNAL(sendAddNewSession()),this,SLOT(addSession()));
    ui->clientsContainer->setStyleSheet("QGroupBox {\
                                        border: 2px solid gray;\
                                        border-radius: 5px;\
                                        margin-top: 1.3em;\
                                       } QGroupBox::title { subcontrol-origin: margin;\
     subcontrol-position: top left;\
     padding:0 3px;\
 }");
    ui->overviewContainer->setStyleSheet("QGroupBox#overviewContainer {\
                                             border: 2px solid gray;\
                                             border-radius: 5px;\
                                             margin-top: 1.3em;\
                                            } QGroupBox::title { subcontrol-origin: margin;\
          subcontrol-position: top left;\
          padding:0 3px;\
      }");
    ui->sessionOverviewGroupBox->setStyleSheet("QGroupBox {\
                                               border: 2px solid gray;\
                                               border-radius: 5px;\
                                               margin-top: 1.3em;\
                                              } QGroupBox::title { subcontrol-origin: margin;\
                                                                   subcontrol-position: top left; padding:0 13px;}");

    // Update Fields for current record
    PopulateView();

    _unregisterSavePendingId = Mediator::Register(MKEY_GUI_MP_SAVE_PENDING, [this](MediatorArg arg){Q_UNUSED(arg);UpdateSignaled();});
    _unregisterPopulateId = Mediator::Register(MKEY_GUI_MP_POPULATE, [this](MediatorArg arg){Q_UNUSED(arg);PopulateView();});
    _unregisterPersistMPId = Mediator::Register(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){SaveCompleted(arg);});

}

MediationProcessView::~MediationProcessView()
{
    Mediator::Unregister(MKEY_GUI_MP_SAVE_PENDING, _unregisterSavePendingId);
    Mediator::Unregister(MKEY_GUI_MP_POPULATE, _unregisterPopulateId);
    Mediator::Unregister(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, _unregisterPersistMPId);
    delete _mediationProcessStatusForm;
//    delete _mediationSessionForm;
    delete ui;
}

void MediationProcessView::PopulateView()
{
    bool saved = (bool)_mediationProcess;
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();

    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
//    _mediationProcessStatusForm->SetSavedLabel(saved);
     _mediationProcess->updateClientSessions(_mediationProcess->GetParties()->size());
    // PARTY!
    AddPartyTabs(_mediationProcess->GetParties());

    // Update Session Browser
    Mediator::Call(MKEY_DOCK_SET_SESSIONS, _mediationProcess->getMediationSessionVector());
    // Update Notes Browser
    Mediator::Call(MKEY_DOCK_SET_NOTES, _mediationProcess->GetNotes());
    // Update Mediations Browser
    Mediator::Call(MKEY_DOCK_REFRESH_MEDIATIONS);

    // Session detail.
//    if(_mediationProcess->getMediationSessionVector()->size() > 0 )
//    {
//        _noSession->hide();
//         _mediationSessionForm->setMediationSession(_mediationProcess->getMediationSessionVector()->at(0));
//        _mediationSessionForm->show();

//    }
//    else
//    {
//        _mediationSessionForm->hide();
//        _noSession->show();
//    }

    // Each View can setup it's own toolbar buttons
    ConfigureToolbar();

    diplaySessions();
}
void MediationProcessView::addSession()
{
    _mediationProcess->addMediation();
    //_mediationProcess->updateClientSessions(_mediationProcess->GetParties()->size());
    PopulateView();
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Record", this, SLOT(SaveMediationPressed()), QIcon(":images/save.png"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Close Record", this, SLOT(CloseMediationPressed()), QIcon(":images/close.jpg"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Mediation Browser", this, SLOT(ShowMediationBrowserPressed()), QIcon(":images/mp_search.jpg"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Session Browser", this, SLOT(ShowSessionBrowserPressed()), QIcon(":images/session_search.jpg"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Notes Browser", this, SLOT(ShowNotesBrowserPressed()), QIcon(":images/notes.jpg"));
    toolbar.GetToolbar()->addSeparator();
}

void MediationProcessView::SaveMediationPressed()
{
    // Assign mediation ID's to the notes.
    foreach(Note* note, *_mediationProcess->GetNotes())
        note->SetMediationId(_mediationProcess->GetId());

    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";
    Mediator::Call(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _mediationProcess);
}

void MediationProcessView::CloseMediationPressed()
{
    // To do - Check if they want to save


    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}

void MediationProcessView::SearchForMediationPressed()
{
    qDebug() << "SEARCH MEDIATION PRESSED - Toolbar manager.";
}

void MediationProcessView::ShowMediationBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_MEDIATION_BROWSER);
    PopulateView();
}

void MediationProcessView::ShowNotesBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_NOTES_BROWSER);
    PopulateView();
}

void MediationProcessView::ShowSessionBrowserPressed()
{
    Mediator::Call(MKEY_GUI_SHOW_SESSIONS_BROWSER);
    PopulateView();
}

void MediationProcessView::SetMediationProcess(MediationProcess* process)
{
    _mediationProcess = process;
    PopulateView();
}

void MediationProcessView::AddPartyTabs(PartyVector* parties)
{
    if(parties && parties->size())
    {
        ui->noClientsLabel->setVisible(false);
        ui->partyTabWidget->setVisible(true);
        ui->partyTabWidget->clear();

        for(size_t i=0; i<parties->size(); ++i)
        {
            Party* partyToAdd = parties->at(i);
            PartyForm* curPartyForm = (PartyForm*)ui->partyTabWidget->widget(i);
            if(partyToAdd)
            {
                Party* curParty = nullptr;
                if(curPartyForm)
                    curParty = curPartyForm->GetParty();
                if(partyToAdd != curParty)
                {
                    PartyForm* pForm = new PartyForm(ui->partyTabWidget, partyToAdd);
                    ui->partyTabWidget->addTab(pForm, partyToAdd->GetPrimary()->FullName() );
                    connect(pForm,SIGNAL(SaveSignaled()),this,SLOT(SaveSignaled()));
                }
            }
        }
    }
    else
    {
        ui->noClientsLabel->setVisible(true);
        ui->partyTabWidget->setVisible(false);
    }
}

void MediationProcessView::diplaySessions()
{
    ui->sessionTabWidget->clear();
    for(int i = 0; i < (int)_mediationProcess->getMediationSessionVector()->size(); i++)
    {
        ui->sessionTabWidget->addTab(new MediationSessionForm(this, _mediationProcess->getMediationSessionVector()->at(i)), ("Session " + QString::number(ui->sessionTabWidget->count())));
    }
}

void MediationProcessView::on_addCientPushButton_clicked()
{

    Party* newParty = new Party();
    _mediationProcess->AddParty(newParty);
    PartyForm* pForm = new PartyForm(ui->partyTabWidget, newParty);
    ui->partyTabWidget->addTab(pForm, newParty->GetPrimary()->FullName() );
    connect(pForm,SIGNAL(SaveSignaled()),this,SLOT(SaveSignaled()));
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    PopulateView();
    ui->partyTabWidget->setCurrentIndex(ui->partyTabWidget->count()-1);
}

void MediationProcessView::on_removeClientPushButton_clicked()
{
    _mediationProcess->removeParty(ui->partyTabWidget->currentIndex());

    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    PopulateView();
}

void MediationProcessView::SaveSignaled()        // Child process signals a save
{
    Mediator::Call(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _mediationProcess);
    PopulateView();
}

void MediationProcessView::UpdateSignaled()      // Child process signals a change occured
{
    // TO DO - Send session to BL
    //    Mediator::Call(MKEY_GUI_, _mediationProcess);
//    PopulateView();
}

void MediationProcessView::SaveCompleted(MediatorArg arg)
{
    if(arg.IsSuccessful())
    {
        MediationProcess* mp = arg.getArg<MediationProcess*>();
        if(mp)
        {
            // Update with all the latest ID's etc.
            SetMediationProcess(mp);
        }
    }
}


