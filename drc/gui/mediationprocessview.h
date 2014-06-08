#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include "contactrecorddataview.h"
#include "intakeform.h"
#include "mediationsession.h"
#include "detailsview.h"

namespace Ui {
class MediationProcessView;
}

class MediationProcessView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessView(QWidget *parent = 0);
    ~MediationProcessView();
    int getNumberOfParty();

private slots:

    void on_toolBox_currentChanged(int index);

private:
    Ui::MediationProcessView *ui;
    IntakeForm *_localIntakeForm;
    QTabWidget *_MediationSessionTabWidget;
    MediationSession *_localMediationSession;
    DetailsView *_localDetailsView;
    int _numberOfParties;
};

#endif // CONTACTRECORDVIEW_H
