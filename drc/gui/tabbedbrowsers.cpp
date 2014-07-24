#include "tabbedbrowsers.h"
#include "ui_tabbedbrowsers.h"

#include "mediationbrowser.h"
#include "sessionsbrowser.h"
#include "Mediator.h"
#include "MediatorKeys.h"

#include <QDebug>

const QString TNAME_PROCESSES = "Mediation Browser";
const QString TNAME_SESSIONS = "Sessions Browser";
const QString TNAME_NOTES = "Notes Browser";


TabbedBrowsers::TabbedBrowsers(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabbedBrowsers)
    , _mpBrowser(nullptr)
    , _sessionsBrowser(nullptr)
    , _notesBrowser(nullptr)

{
    ui->setupUi(this);

    Configure();

    _unregisterSetNotes = Mediator::Register(MKEY_DOCK_SET_NOTES, [this](MediatorArg arg){ NotesChanged(arg); });
}

TabbedBrowsers::~TabbedBrowsers()
{
    Mediator::Unregister(MKEY_DOCK_SET_NOTES, _unregisterSetNotes);
    delete ui;
}


void TabbedBrowsers::NotesChanged(MediatorArg arg)
{
    // If the vector is null - there's no MP. Hide the notes browser!
//    if(_notesBrowser->isVisible())
//        _notesBrowser->setHidden(!arg.getArg<MediationNotesVector*>());
        setTabEnabled(_notesBrowserIndex, arg.getArg<MediationNotesVector*>());
}

void TabbedBrowsers::Configure()
{
    // Remove the two default pages.
    this->removeTab(0);
    this->removeTab(0);

    // Add Our Widgets
    EnableMediationsTable();
    //EnableSessionsTable(nullptr);
    EnableNotesTable(nullptr);

    _currentBrowserType = MPBROWSER_MEDIATION;
}


//////// Mediation Process Table ///////////
void TabbedBrowsers::DisableMediationsTable()
{
    if(_mpBrowserIndex >= 0)
    {
        removeTab(_mpBrowserIndex);
        _mpBrowserIndex = -1;
        _mpBrowser = nullptr;
    }
}

void TabbedBrowsers::EnableMediationsTable(MediationTableSortTypes sortType)
{
    if(!_mpBrowser)
    {
        _mpBrowser = new MediationBrowser(this, sortType);
        connect(_mpBrowser, SIGNAL(on_mediationProcessSelected(MediationProcess*)), this, SLOT(DoMPSelected(MediationProcess*)));
        _mpBrowserIndex = this->addTab(_mpBrowser, TNAME_PROCESSES);
        setTabEnabled(_mpBrowserIndex, true);
        setCurrentIndex(_mpBrowserIndex);
        qDebug() << "_mpBrowserIndex = " << _mpBrowserIndex;
    }
    else
    {
        _mpBrowser->LoadTableData(sortType);
        setTabEnabled(_mpBrowserIndex, true);
    }
}

void TabbedBrowsers::DisableSessionsTable()
{
    if(_sessionsBrowserIndex >= 0)
        setTabEnabled(_sessionsBrowserIndex, false);
}

void TabbedBrowsers::EnableSessionsTable(MediationSessionVector* sessions)
{
    if(!_sessionsBrowser)
    {
        _sessionsBrowser = new SessionsBrowser(this, sessions);
        _sessionsBrowserIndex = this->addTab(_sessionsBrowser, TNAME_SESSIONS);
        setTabEnabled(_sessionsBrowserIndex, true);
        qDebug() << "_sessionsBrowserIndex = " << _sessionsBrowserIndex;
    }
    else
    {
        _sessionsBrowser->SetSessions(sessions);
        setTabEnabled(_sessionsBrowserIndex, true);
    }
}

void TabbedBrowsers::EnableNotesTable(MediationNotesVector* notes)
{
    if(!_notesBrowser)
    {
        _notesBrowser = new NotesBrowser(this, notes);
        _notesBrowserIndex = this->addTab(_notesBrowser, TNAME_NOTES);
        setTabEnabled(_notesBrowserIndex, true);
        qDebug() << "_sessionsBrowserIndex = " << _notesBrowserIndex;
    }
    else
    {
        _notesBrowser->SetNotes(notes);
        setTabEnabled(_notesBrowserIndex, true);
    }
}

void TabbedBrowsers::DisableNotesTable()
{
    if(_sessionsBrowserIndex >= 0)
    {
        setTabEnabled(_sessionsBrowserIndex, false);
        _sessionsBrowserIndex = -1;
    }
}

bool TabbedBrowsers::IsShowingBrowser(MPBrowserTypes browserType)
{
    switch(browserType)
    {
    case MPBROWSER_MEDIATION: return currentIndex() == _mpBrowserIndex;
    case MPBROWSER_NOTES: return currentIndex() == _notesBrowserIndex;
    case MPBROWSER_SESSIONS: return currentIndex() == _sessionsBrowserIndex;
    default: return false;
    }
}

void TabbedBrowsers::ShowBrowser(MPBrowserTypes browserType)
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
