#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QDebug>
#include "contactrecorddataview.h"
#include "intakeform.h"
#include "mediationsession.h"
namespace Ui {
class ContactRecordView;
}

class ContactRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit ContactRecordView(QWidget *parent = 0);
    ~ContactRecordView();
    int getNumberOfParty();

private slots:

    void on_toolBox_currentChanged(int index);

private:
    Ui::ContactRecordView *ui;
    IntakeForm *_localIntakeForm;
    QTabWidget *_MediationSessionTabWidget;
    MediationSession *_localMediationSession;
    int _numberOfParties;
};

#endif // CONTACTRECORDVIEW_H
