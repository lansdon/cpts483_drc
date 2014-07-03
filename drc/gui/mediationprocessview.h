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

class MediationProcessView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessView(QWidget *parent = 0, MediationProcess* mediationProcess = nullptr);
    ~MediationProcessView();

    int getNumberOfParty();

    void SetMediationProcess(MediationProcess* process);
    MediationProcess* GetMediationProcess() { return _mediationProcess; }

    // Populate Views (allowing this to be called publicly as a central place to update all views
    // associated with this MP)
    void PopulateView();

private slots:
    // Toolbar Buttons
    void SaveMediationPressed();
    void SearchForMediationPressed();
    void ShowMediationBrowserPressed();
    void ShowSessionBrowserPressed();
    void ShowNotesBrowserPressed();
    // Add new session
    void addSession();

    void on_addCientPushButton_clicked();

    void on_removeClientPushButton_clicked();

    void SaveSignaled();        // Child process signals a save
    void UpdateSignaled();      // Child process signals a change occured

private:
    Ui::MediationProcessView *ui;

    MediationProcess* _mediationProcess;

     // Toolbox + Children (pages)
     MediationProcessStatusForm *_mediationProcessStatusForm;
     SessionOverview *_sessionOverview;
     MediationSessionForm *_mediationSessionForm;
     NoSessionsView *_noSession;

     // Setup GUI Helpers
    void ConfigureToolbar();
    void ConfigureToolbox();

    // Clients/Parties Tabs
    void AddPartyTabs(PartyVector* parties);

    // Sessions Table
    QTableWidget* _sessionTable;
    void configSessionTable();
    void PopulateSessionTable();
    void on_sessiontTableWidget_itemSelectionChanged();

    void SaveCompleted(MediatorArg arg);

    // Unregister Mediator Ids
    MediatorId _unregisterSavePendingId;
    MediatorId _unregisterPopulateId;
    MediatorId _unregisterPersistMPId;
};

#endif // CONTACTRECORDVIEW_H
