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

/*!
 * \brief The TabbedBrowsers class
 */
class TabbedBrowsers : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabbedBrowsers(QWidget *parent = 0);
    ~TabbedBrowsers();
    /*!
     * \brief IsShowingBrowser
     * \param browserType
     * \return
     */
    bool IsShowingBrowser(MPBrowserTypes browserType);
    /*!
     * \brief ShowBrowser
     * \param browserType
     */
    void ShowBrowser(MPBrowserTypes browserType);
    /*!
     * \brief GetCurrentBrowserType
     * \return
     */
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

    /*!
     * \brief Configure
     */
    void Configure();
    /*!
     * \brief EnableMediationsTable
     * \param sortType
     */
    void EnableMediationsTable(MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    /*!
     * \brief EnableSessionsTable
     * \param sessions
     */
    void EnableSessionsTable(MediationSessionVector* sessions);
    /*!
     * \brief EnableNotesTable
     * \param notes
     */
    void EnableNotesTable(MediationNotesVector* notes);
    /*!
     * \brief DisableMediationsTable
     */
    void DisableMediationsTable();
    /*!
     * \brief DisableSessionsTable
     */
    void DisableSessionsTable();
    /*!
     * \brief DisableNotesTable
     */
    void DisableNotesTable();

    // Use this to disable notes browser if the vector is nullptr.
    /*!
     * \brief NotesChanged
     * \param arg
     */
    void NotesChanged(MediatorArg arg);

    MediatorId _unregisterSetNotes;
signals:
    /*!
     * \brief MPSelected
     * \param process
     */
    void MPSelected(MediationProcess* process);

public slots:
    /*!
     * \brief DoMPSelected
     * \param process
     */
    void DoMPSelected(MediationProcess* process) { emit MPSelected(process); }

};

#endif // TABBEDBROWSERS_H
