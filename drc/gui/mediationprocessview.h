#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include <QToolBox>
#include "contactrecorddataview.h"
#include "DRCModels.h"
#include "mediationprocessstatusform.h"
#include "mediationsessionform.h"
#include "sessionoverview.h"
#include "nosessionsview.h"

namespace Ui {
class MediationProcessView;
}

/*!
 * \brief The MediationProcessView class
 */
class MediationProcessView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessView(QWidget *parent = 0, MediationProcess* mediationProcess = nullptr);
    ~MediationProcessView();
    /*!
     * \brief getNumberOfParty
     * \return
     */
    int getNumberOfParty();
    /*!
     * \brief SetMediationProcess
     * \param process
     */
    void SetMediationProcess(MediationProcess* process);
    /*!
     * \brief GetMediationProcess
     * \return
     */
    MediationProcess* GetMediationProcess() { return _mediationProcess; }

    // Populate Views (allowing this to be called publicly as a central place to update all views
    // associated with this MP)
    /*!
     * \brief PopulateView
     */
    void PopulateView();
    /*!
     * \brief getChangesPending
     * \return
     */
    bool getChangesPending() const { return _changesPending; }

private slots:
    // Toolbar Buttons
    /*!
     * \brief SaveMediationPressed
     */
    void SaveMediationPressed();
    /*!
     * \brief CloseMediationPressed
     */
    void CloseMediationPressed();
    /*!
     * \brief SearchForMediationPressed
     */
    void SearchForMediationPressed();
    /*!
     * \brief ShowMediationBrowserPressed
     */
    void ShowMediationBrowserPressed();
    /*!
     * \brief ShowSessionBrowserPressed
     */
    void ShowSessionBrowserPressed();
    /*!
     * \brief ShowNotesBrowserPressed
     */
    void ShowNotesBrowserPressed();
    /*!
     * \brief PrintMediationProcessPressed
     */
    void PrintMediationProcessPressed();

    // Add new session
    /*!
     * \brief addSession
     */
    void addSession();
    /*!
     * \brief on_addCientPushButton_clicked
     */
    void on_addCientPushButton_clicked();
    /*!
     * \brief on_removeClientPushButton_clicked
     */
    void on_removeClientPushButton_clicked();
    /*!
     * \brief SaveSignaled
     */
    void SaveSignaled();        // Child process signals a save
    /*!
     * \brief UpdateSignaled
     */
    void UpdateSignaled();      // Child process signals a change occured
    /*!
     * \brief on_addSessionPushButton_clicked
     */
    void on_addSessionPushButton_clicked();
    /*!
     * \brief on_sessionTabWidget_tabCloseRequested
     * \param index
     */
    void on_sessionTabWidget_tabCloseRequested(int index);
    /*!
     * \brief on_partyTabWidget_tabCloseRequested
     * \param index
     */
    void on_partyTabWidget_tabCloseRequested(int index);

    void on_notesPushButton_clicked();

private:
    Ui::MediationProcessView *ui;

    MediationProcess* _mediationProcess;
    bool _changesPending;

     // Toolbox + Children (pages)
     MediationProcessStatusForm *_mediationProcessStatusForm;
     SessionOverview *_sessionOverview;
     MediationSessionForm *_mediationSessionForm;
     NoSessionsView *_noSession;

    // Setup GUI Helpers
     /*!
     * \brief ConfigureToolbar
     */
    void ConfigureToolbar();
    /*!
     * \brief ConfigureToolbox
     */
    void ConfigureToolbox();


    // Clients/Parties Tabs
    /*!
     * \brief AddPartyTabs
     * \param parties
     */
    void AddPartyTabs(PartyVector* parties);

    // Sessions Table
    QTableWidget* _sessionTable;
    /*!
     * \brief configSessionTable
     */
    void configSessionTable();
    /*!
     * \brief PopulateSessionTable
     */
    void PopulateSessionTable();
    /*!
     * \brief on_sessiontTableWidget_itemSelectionChanged
     */
    void on_sessiontTableWidget_itemSelectionChanged();
    /*!
     * \brief diplaySessions
     */
    void diplaySessions();
    /*!
     * \brief SaveCompleted
     * \param arg
     */
    void SaveCompleted(MediatorArg arg);
    void sessionAddButtonEnable();

    // Unregister Mediator Ids
    MediatorId _unregisterSavePendingId;
    MediatorId _unregisterPopulateId;
    MediatorId _unregisterPersistMPId;
};

#endif // CONTACTRECORDVIEW_H
