#include "mptoolbox.h"
#include "ui_mptoolbox.h"

#include "mediationbrowser.h"
#include "sessionsbrowser.h"
#include "Mediator.h"
#include "MediatorKeys.h"

#include <QDebug>

const QString TNAME_PROCESSES = "Mediation Browser";
const QString TNAME_SESSIONS = "Sessions Browser";
const QString TNAME_NOTES = "Notes Browser";

MPToolBox::MPToolBox(QWidget *parent)
    : QToolBox(parent)
    , ui(new Ui::MPToolBox)
    , _mpBrowser(nullptr)
    , _sessionsBrowser(nullptr)
    , _notesBrowser(nullptr)
{
    ui->setupUi(this);

    Configure();

    _unregisterSetNotes = Mediator::Register(MKEY_DOCK_SET_NOTES, [this](MediatorArg arg){ NotesChanged(arg); });
}

MPToolBox::~MPToolBox()
{
    Mediator::Unregister(MKEY_DOCK_SET_NOTES, _unregisterSetNotes);
    delete ui;
}

void MPToolBox::NotesChanged(MediatorArg arg)
{
    // If the vector is null - there's no MP. Hide the notes browser!
    if(_notesBrowser)
        _notesBrowser->setHidden(!arg.getArg<MediationNotesVector*>());
}

void MPToolBox::Configure()
{
    // Remove the two default pages.
    this->removeItem(0);
    this->removeItem(0);

    // Add Our Widgets
    EnableMediationsTable();
    //EnableSessionsTable(nullptr);
    EnableNotesTable(nullptr);

    _currentBrowserType = MPBROWSER_MEDIATION;
}


//////// Mediation Process Table ///////////
void MPToolBox::DisableMediationsTable()
{
    if(_mpBrowserIndex >= 0)
    {
        removeItem(_mpBrowserIndex);
        _mpBrowserIndex = -1;
        _mpBrowser = nullptr;
    }
}

void MPToolBox::EnableMediationsTable(MediationTableSortTypes sortType)
{
    if(!_mpBrowser)
    {
        _mpBrowser = new MediationBrowser(this, sortType);
        connect(_mpBrowser, SIGNAL(on_mediationProcessSelected(MediationProcess*)), this, SLOT(DoMPSelected(MediationProcess*)));
        _mpBrowserIndex = this->addItem(_mpBrowser, TNAME_PROCESSES);
        setItemEnabled(_mpBrowserIndex, true);
        setCurrentIndex(_mpBrowserIndex);
        qDebug() << "_mpBrowserIndex = " << _mpBrowserIndex;
    }
    else
    {
        _mpBrowser->LoadTableData(sortType);
        setItemEnabled(_mpBrowserIndex, true);
    }
}

void MPToolBox::DisableSessionsTable()
{
    if(_sessionsBrowserIndex >= 0)
        setItemEnabled(_sessionsBrowserIndex, false);
}

void MPToolBox::EnableSessionsTable(MediationSessionVector* sessions)
{
    if(!_sessionsBrowser)
    {
        _sessionsBrowser = new SessionsBrowser(this, sessions);
        _sessionsBrowserIndex = this->addItem(_sessionsBrowser, TNAME_SESSIONS);
        setItemEnabled(_sessionsBrowserIndex, true);
        qDebug() << "_sessionsBrowserIndex = " << _sessionsBrowserIndex;
    }
    else
    {
        _sessionsBrowser->SetSessions(sessions);
        setItemEnabled(_sessionsBrowserIndex, true);
    }
}

void MPToolBox::EnableNotesTable(MediationNotesVector* notes)
{
    if(!_notesBrowser)
    {
        _notesBrowser = new NotesBrowser(this, notes);
        _notesBrowserIndex = this->addItem(_notesBrowser, TNAME_NOTES);
        setItemEnabled(_notesBrowserIndex, true);
        qDebug() << "_sessionsBrowserIndex = " << _notesBrowserIndex;
    }
    else
    {
        _notesBrowser->SetNotes(notes);
        setItemEnabled(_notesBrowserIndex, true);
    }
}

void MPToolBox::DisableNotesTable()
{
    if(_sessionsBrowserIndex >= 0)
    {
        setItemEnabled(_sessionsBrowserIndex, false);
        _sessionsBrowserIndex = -1;
    }
}

bool MPToolBox::IsShowingBrowser(MPBrowserTypes browserType)
{
    switch(browserType)
    {
    case MPBROWSER_MEDIATION: return currentIndex() == _mpBrowserIndex;
    case MPBROWSER_NOTES: return currentIndex() == _notesBrowserIndex;
    case MPBROWSER_SESSIONS: return currentIndex() == _sessionsBrowserIndex;
    default: return false;
    }
}

void MPToolBox::ShowBrowser(MPBrowserTypes browserType)
{
    _currentBrowserType = browserType;
    switch(browserType)
    {
    case MPBROWSER_NOTES: setCurrentIndex(_notesBrowserIndex); break;
    case MPBROWSER_SESSIONS: setCurrentIndex(_sessionsBrowserIndex); break;
    case MPBROWSER_MEDIATION:
    default:
        setCurrentIndex(_mpBrowserIndex);
        _currentBrowserType = MPBROWSER_MEDIATION;
    }
}

