#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include <QToolBox>
#include "contactrecorddataview.h"
#include "mediationsession.h"
#include "mediationprocess.h"
#include "mediationprocessstatusform.h"
#include "partiescontainerform.h"
#include "mediationsessionform.h"

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

private slots:
    // Toolbar Buttons
    void SaveMediationPressed();
    void SearchForMediationPressed();
    void ShowRecentPressed();

    void savePersonContactFromFarAway(Person*value);

private:
    Ui::MediationProcessView *ui;

    MediationProcess* _mediationProcess;

     // Toolbox + Children (pages)
     MediationProcessStatusForm *_mediationProcessStatusForm;
//     PartiesContainerForm *_partiesContainerForm;
//     MediationSessionForm *_mediationSessionForm;

     // Setup GUI Helpers
    void ConfigureToolbar();
    void ConfigureToolbox();

    // Populate Views
    void PopulateView(MediationProcess *value);

    // Clients/Parties Tabs
    void AddPartyTabs(PartyVector* parties);

    // Sessions Table
    QTableWidget* _sessionTable;
    void configSessionTable();
    void PopulateSessionTable();
    void on_sessiontTableWidget_itemSelectionChanged();
};

#endif // CONTACTRECORDVIEW_H
