#include "mptoolbox.h"
#include "ui_mptoolbox.h"

#include "mediationbrowser.h"
#include "sessionsbrowser.h"

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
}

MPToolBox::~MPToolBox()
{
    delete ui;
}


void MPToolBox::Configure()
{
    // Remove the two default pages.
    this->removeItem(0);
    this->removeItem(0);

    // Add Our Widgets
    EnableMediationsTable();
    EnableSessionsTable(nullptr);
    EnableNotesTable(nullptr);
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

bool IsShowingBrowser(MPBrowserTypes browserType)
{

}

void ShowBrowser(MPBrowserTypes browserType)
{

}

