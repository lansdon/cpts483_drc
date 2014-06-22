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
     QToolBox* _toolBox;
     MediationProcessStatusForm *_mediationProcessStatusForm;
     PartiesContainerForm *_partiesContainerForm;
     MediationSessionForm *_mediationSessionForm;

     // Setup GUI Helpers
    void ConfigureToolbar();
    void ConfigureToolbox();

    // Populate Views
    void PopulateView(MediationProcess *value);

};

#endif // CONTACTRECORDVIEW_H
