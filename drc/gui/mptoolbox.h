#ifndef MPTOOLBOX_H
#define MPTOOLBOX_H

#include <QToolBox>

#include "drctypes.h"
#include "mediationbrowser.h"
#include "sessionsbrowser.h"
#include "mediationprocess.h"
#include "notesbrowser.h"
#include "Mediator.h"

/// List of MP browser types
enum MPBrowserTypes
{
    MPBROWSER_NONE,
    MPBROWSER_MEDIATION,
    MPBROWSER_SESSIONS,
    MPBROWSER_NOTES
};

namespace Ui {
class MPToolBox;
}

/*!
 * \brief The MPToolBox class
 */
class MPToolBox : public QToolBox
{
    Q_OBJECT

public:
    explicit MPToolBox(QWidget *parent = 0);
//    static MPToolBox& Instance(QWidget *parent = 0);
    ~MPToolBox();
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
    Ui::MPToolBox *ui;

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

#endif // MPTOOLBOX_H
