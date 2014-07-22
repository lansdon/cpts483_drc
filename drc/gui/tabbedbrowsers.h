#ifndef TABBEDBROWSERS_H
#define TABBEDBROWSERS_H

#include <QTabWidget>

#include "drctypes.h"
#include "mediationbrowser.h"
#include "sessionsbrowser.h"
#include "mediationprocess.h"
#include "notesbrowser.h"
#include "Mediator.h"
#include "mptoolbox.h"  // for browsers types


namespace Ui {
class TabbedBrowsers;
}

class TabbedBrowsers : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabbedBrowsers(QWidget *parent = 0);
    ~TabbedBrowsers();

    bool IsShowingBrowser(MPBrowserTypes browserType);
    void ShowBrowser(MPBrowserTypes browserType);
    MPBrowserTypes GetCurrentBrowserType() { return _currentBrowserType; }
private:
    Ui::TabbedBrowsers *ui;

    MPBrowserTypes _currentBrowserType;
    MediationBrowser* _mpBrowser;
    SessionsBrowser* _sessionsBrowser;
    NotesBrowser* _notesBrowser;
    // Track which indices the tables use (for enable/disable)
    int _mpBrowserIndex;
    int _sessionsBrowserIndex;
    int _notesBrowserIndex;

    void Configure();

    void EnableMediationsTable(MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    void EnableSessionsTable(MediationSessionVector* sessions);
    void EnableNotesTable(MediationNotesVector* notes);

    void DisableMediationsTable();
    void DisableSessionsTable();
    void DisableNotesTable();

    // Use this to disable notes browser if the vector is nullptr.
    void NotesChanged(MediatorArg arg);

    MediatorId _unregisterSetNotes;
signals:
    void MPSelected(MediationProcess* process);

public slots:
    void DoMPSelected(MediationProcess* process) { emit MPSelected(process); }

};

#endif // TABBEDBROWSERS_H
