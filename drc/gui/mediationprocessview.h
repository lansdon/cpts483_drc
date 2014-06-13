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

//    void on_toolBox_currentChanged(int index);




    void on_MediationProcessTableWidget_itemSelectionChanged();

private:
    Ui::MediationProcessView *ui;
//    IntakeForm *_localIntakeForm;
    QTabWidget *_MediationSessionTabWidget;
//    MediationSession *_localMediationSession;
//    DetailsView *_localDetailsView;
//    int _numberOfParties;
    QTableWidget *MediationProcessTableView;
    QStringList MediationProcessTableViewHeader;
    void configMediationProcecssViewTable();
    void PopulateMediationProcessTable();
    void PopulateView(MediationProcess *value);
    MediationProcess* _mediationProcess;
    MediationProcessVector *_localMediationProcessVector;
     QToolBox* toolBox;
     int MediationProcessCurrentRow;
     MediationProcessStatusForm *_localMediationProcessStatusForm;
     PartiesContainerForm *_localPartiesContainerForm;
     MediationSession *_localMediationSession;
};

#endif // CONTACTRECORDVIEW_H
