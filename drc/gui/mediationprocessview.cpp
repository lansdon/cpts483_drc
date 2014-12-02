#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"

// QT
#include <QWidget>
#include <QListWidget>
#include <QToolBox>
#include <QDebug>
#include <QMessageBox>

// DRC
#include "mediationprocessstatusform.h"
#include "toolbarmanager.h"
#include "DRCModels.h"
#include "MediatorKeys.h"
#include "nosessionsview.h"
#include "partyform.h"
#include "persondetailsform.h"

MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess *mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);
    if(_mediationProcess->GetParties()->size() == 0)
        _mediationProcess->AddParty(new Party());
    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);
    _changesPending = true;
    _notes_Changed = false;
    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);
    ui->clientsContainer->setStyleSheet("QGroupBox {\
                                        border: 2px solid gray;\
                                        border-radius: 5px;\
                                        margin-top: 8px;\
                                       } QGroupBox::title { subcontrol-origin: margin;\
     subcontrol-position: top left;\
     padding:0 3px;\
 }");
    ui->overviewContainer->setStyleSheet("QGroupBox#overviewContainer {\
                                             border: 2px solid gray;\
                                             border-radius: 5px;\
                                             margin-top: 8px;\
                                            } QGroupBox::title { subcontrol-origin: margin;\
          subcontrol-position: top left;\
          padding:0 3px;\
      }");
    ui->sessionOverviewGroupBox->setStyleSheet("QGroupBox {\
                                               border: 2px solid gray;\
                                               border-radius: 5px;\
                                               margin-top: 8px;\
                                              } QGroupBox::title { subcontrol-origin: margin;\
                                                                   subcontrol-position: top left; padding:0 13px;}");

    // Update Fields for current record

    PopulateView();

    _unregisterSavePendingId = Mediator::Register(MKEY_GUI_MP_SAVE_PENDING, [this](MediatorArg arg){Q_UNUSED(arg);UpdateSignaled();});
//    _unregisterPopulateId = Mediator::Register(MKEY_GUI_MP_POPULATE, [this](MediatorArg arg){Q_UNUSED(arg);PopulateView();});
    _unregisterPersistMPId = Mediator::Register(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){SaveCompleted(arg);});
    _unregisterNotesChanged = Mediator::Register(MKEY_GUI_NOTE_CHANGED, [this](MediatorArg arg){notes_changed(arg);});
}

MediationProcessView::~MediationProcessView()
{
    Mediator::Unregister(MKEY_GUI_MP_SAVE_PENDING, _unregisterSavePendingId);
//    Mediator::Unregister(MKEY_GUI_MP_POPULATE, _unregisterPopulateId);
    Mediator::Unregister(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, _unregisterPersistMPId);
    delete _mediationProcessStatusForm;
    delete ui;
}

void MediationProcessView::notes_changed(MediatorArg arg)
{
    auto isChange = arg.getArg<bool *>();
    if(*isChange)
        _notes_Changed = true;
    else
        _notes_Changed = false;
}

void MediationProcessView::PopulateView()
{
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();


    // CLIENTS
    _mediationProcess->updateClientSessions(_mediationProcess->GetParties()->size());
    // PARTY!
    AddPartyTabs(_mediationProcess->GetParties());

    MediatorArg arg;
    arg.SetArg(_mediationProcess);
    Mediator::Call(MKEY_GUI_SEND_MP_POINTER,arg);
    // Update Session Browser
//    Mediator::Call(MKEY_DOCK_SET_SESSIONS, _mediationProcess->getMediationSessionVector());
    // Update Notes Browser
    Mediator::Call(MKEY_DOCK_SET_NOTES, _mediationProcess->GetNotes());
    // Update Mediations Browser
    Mediator::Call(MKEY_DOCK_REFRESH_MEDIATIONS);

    // Each View can setup it's own toolbar buttons
    ConfigureToolbar();
    //sessionAddButtonEnable();
    diplaySessions();
    // SUMMARY
    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
}

void MediationProcessView::sessionAddButtonEnable()
{
    ui->addSessionPushButton->setEnabled(false);
    if(_mediationProcess->GetInternalState() >= PROCESS_INTERNAL_STATE_CLIENT_INFO)
        ui->addSessionPushButton->setEnabled(true);
}

void MediationProcessView::addSession()
{
    _mediationProcess->addMediation();
    //_mediationProcess->updateClientSessions(_mediationProcess->GetParties()->size());
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
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
//    toolbar.AddAction("Session Browser", this, SLOT(ShowSessionBrowserPressed()), QIcon(":images/session_search.jpg"));
//    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Notes Browser", this, SLOT(ShowNotesBrowserPressed()), QIcon(":images/notes.jpg"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Print Intake", this, SLOT(PrintMediationProcessPressed()), QIcon(":images/printer-icon.png"));
    toolbar.GetToolbar()->addSeparator();
}

void MediationProcessView::SaveMediationPressed()
{
    // Assign mediation ID's to the notes.
    if(_notes_Changed)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            foreach(Note* note, *_mediationProcess->GetNotes())
                note->SetMediationId(_mediationProcess->GetId());
            _changesPending = false;
            qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";
            Mediator::Call(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _mediationProcess);
            bool* change = new bool(false);
            Mediator::Call(MKEY_GUI_NOTE_CHANGED,change);
        }
    }
    else
    {
        foreach(Note* note, *_mediationProcess->GetNotes())
            note->SetMediationId(_mediationProcess->GetId());

        qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";
        Mediator::Call(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _mediationProcess);
        bool* change = new bool(false);
        Mediator::Call(MKEY_GUI_NOTE_CHANGED,change);
    }

}

void MediationProcessView::CloseMediationPressed()
{

    if(_changesPending)
    {
        if(_notes_Changed)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to close?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    // Pass null to notes browser to disable it.
                    Mediator::Call(MKEY_DOCK_SET_NOTES, nullptr);
                    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
                    _notes_Changed = false;
                }
            }

        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to close?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                // Pass null to notes browser to disable it.
                Mediator::Call(MKEY_DOCK_SET_NOTES, nullptr);
                Mediator::Call(MKEY_GUI_ENABLE_MENUS);
            }
        }

    }
    else if(_notes_Changed)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            Mediator::Call(MKEY_DOCK_SET_NOTES, nullptr);
            Mediator::Call(MKEY_GUI_ENABLE_MENUS);
            _notes_Changed = false;
        }
    }
    else
    {
        // Pass null to notes browser to disable it.
        Mediator::Call(MKEY_DOCK_SET_NOTES, nullptr);
        Mediator::Call(MKEY_GUI_ENABLE_MENUS);
    }
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

    if(_mediationProcess->GetParties()->size() == 0)
        _mediationProcess->AddParty(new Party());
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
                    PersonDetailsForm* pForm = new PersonDetailsForm(ui->partyTabWidget, partyToAdd->GetPrimary());
                    //PartyForm* pForm = new PartyForm(ui->partyTabWidget, partyToAdd);
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
    if(_mediationProcess->getMediationSessionVector()->size() > 0)
    {
        ui->noSessionLabel->setVisible(false);
        ui->sessionTabWidget->setVisible(true);
        for(int i = 0; i < (int)_mediationProcess->getMediationSessionVector()->size(); i++)
        {
            ui->sessionTabWidget->addTab(new MediationSessionForm(this, _mediationProcess->getMediationSessionVector()->at(i)),
                                         (_mediationProcess->getMediationSessionVector()->at(i)->getScheduledDate().toString("MM/dd/yyyy")));
        }
    }
    else
    {
        ui->sessionTabWidget->setVisible(false);
        ui->noSessionLabel->setVisible(true);
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
    _changesPending = true;
    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
    //sessionAddButtonEnable();
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
            _changesPending = false;
            _notes_Changed = false;
        }
    }
}



void MediationProcessView::on_addSessionPushButton_clicked()
{
    _mediationProcess->addMediation();
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    PopulateView();
    ui->sessionTabWidget->setCurrentIndex(ui->sessionTabWidget->count() -  1);

}

void MediationProcessView::on_sessionTabWidget_tabCloseRequested(int index)
{
    QMessageBox msgBox;
    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setText("Are you sure you want to remove the session?");

    int selection = msgBox.exec();
    if(selection == QMessageBox::Yes)
    {
        _mediationProcess->getMediationSessionVector()->erase(_mediationProcess->getMediationSessionVector()->begin() + index);
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
        PopulateView();
    }
}

void MediationProcessView::on_partyTabWidget_tabCloseRequested(int index)
{
    QMessageBox msgBox;
    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setText("Are you sure you want to remove the client?");

    int selection = msgBox.exec();
    if(selection == QMessageBox::Yes)
    {
        _mediationProcess->removeParty(index);
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
        PopulateView();
    }
}

void MediationProcessView::PrintMediationProcessPressed()
{
    //create MP to PDF send current MP to it
    if (_mediationProcess)
    {
        std::cout << "Print Button Pressed!" << std::endl;
        _mediationProcess->PrintMediation();
    }
    //qDebug() << "Print Mediation Pressed!";
}

void MediationProcessView::on_notesPushButton_clicked()
{
    ShowNotesBrowserPressed();
}
