#include "mptoolbox.h"
#include "ui_mptoolbox.h"

#include "mediationprocesstableform.h"
#include "sessionstableform.h"

#include <QDebug>

const QString TNAME_PROCESSES = "Mediation Record Selection";
const QString TNAME_SESSIONS = "Mediation Sessions";
const QString TNAME_NOTES = "Mediation Notes";

MPToolBox::MPToolBox(QWidget *parent)
    : QToolBox(parent)
    , ui(new Ui::MPToolBox)
    , _mpTable(nullptr)
    , _sessionsTable(nullptr)
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
    if(_mpTableIndex >= 0)
    {
        removeItem(_mpTableIndex);
        _mpTableIndex = -1;
        _mpTable = nullptr;
    }
}

void MPToolBox::EnableMediationsTable(MediationTableSortTypes sortType)
{
    if(!_mpTable)
    {
        _mpTable = new MediationProcessTableForm(this, sortType);
        _mpTableIndex = this->addItem(_mpTable, TNAME_PROCESSES);
        setItemEnabled(_mpTableIndex, true);
        setCurrentIndex(_mpTableIndex);
        qDebug() << "_mpTableIndex = " << _mpTableIndex;
    }
    else
    {
        _mpTable->LoadTableData(sortType);
        setItemEnabled(_mpTableIndex, true);
    }
}

void MPToolBox::DisableSessionsTable()
{
    if(_sessionsTableIndex >= 0)
        setItemEnabled(_sessionsTableIndex, false);
}

void MPToolBox::EnableSessionsTable(MediationSessionVector* sessions)
{
    if(!_sessionsTable)
    {
        _sessionsTable = new SessionsTableForm(this, sessions);
        _sessionsTableIndex = this->addItem(_sessionsTable, TNAME_SESSIONS);
        setItemEnabled(_sessionsTableIndex, true);
        qDebug() << "_sessionsTableIndex = " << _sessionsTableIndex;
    }
    else
    {
        _sessionsTable->SetSessions(sessions);
        setItemEnabled(_sessionsTableIndex, true);
    }

}

void MPToolBox::EnableNotesTable(MediationNotesVector* notes)
{

}

