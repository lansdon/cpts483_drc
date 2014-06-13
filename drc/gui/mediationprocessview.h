#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include "contactrecorddataview.h"
#include "mediationsession.h"
#include "detailsview.h"
#include "mediationprocess.h"

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
    void SaveMediationPressed();
    void SearchForMediationPressed();

//    void on_toolBox_currentChanged(int index);

private:
    Ui::MediationProcessView *ui;

    QTabWidget *_MediationSessionTabWidget;

    MediationProcess* _mediationProcess;

    void ConfigureToolbar();

};

#endif // CONTACTRECORDVIEW_H
