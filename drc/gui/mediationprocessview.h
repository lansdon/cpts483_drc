#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include "contactrecorddataview.h"
#include "mediationsession.h"
#include "detailsview.h"
#include "mediationprocess.h"
#include <QToolBox>
#include "mediationprocessstatusform.h"
#include "partiescontainerform.h"

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

    MediationProcess* GetMediationProcess() { return _mediationProcess; }

private slots:
    // Toolbar Buttons
    void SaveMediationPressed();
    void SearchForMediationPressed();
    void ShowRecentPressed();

    void savePersonContactFromFarAway(Person*value);

    void on_MediationProcessTableWidget_itemSelectionChanged();

    void on_MediationProcessTableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MediationProcessView *ui;

//    QTabWidget *_MediationSessionTabWidget;

    MediationProcess* _mediationProcess;

    // Recent Table
    MediationProcessVector *_localMediationProcessVector;
    QTableWidget *MediationProcessTableView;
    QStringList MediationProcessTableViewHeader;    
     int _currentProcessRow;

     // Toolbox + Children (pages)
     QToolBox* toolBox;
     MediationProcessStatusForm *_localMediationProcessStatusForm;
     PartiesContainerForm *_localPartiesContainerForm;
     MediationSession *_localMediationSession;

     // Setup GUI Helpers
    void ConfigureToolbar();
    void ConfigureToolbox();
    void configMediationProcecssViewTable();

    // Populate Views
    void PopulateMediationProcessTable();
    void PopulateView(MediationProcess *value);

};

#endif // CONTACTRECORDVIEW_H
