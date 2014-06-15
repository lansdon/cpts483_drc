#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QWidget>
#include "attorneyandsupportformediationsessionview.h"
#include <vector>
#include "drc_shared/models/Person.h"
#include "drc_shared/models/mediationsessionclass.h"

namespace Ui {
class MediationSession;
}

class MediationSession : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSession(QWidget *parent = 0);
    ~MediationSession();
    void setParties(int input);
    void updateTabs(std::vector<Person *> input);

private slots:
    void on_CancelledRadioButton_toggled(bool checked);

    void on_PendingRadioButton_toggled(bool checked);

    void on_confirmedRadioButton_toggled(bool checked);

    void on_rescheduledRadioButton_toggled(bool checked);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_Fee1LineEdit_editingFinished();

    void on_Fee1PaidCheckBox_toggled(bool checked);

private:
    Ui::MediationSession *ui;
    std::vector<AttorneyAndSupportForMediationSessionView *> _attorneyAndSupportVector;
    MediationSessionClass _localMediationSessionClass;
};

#endif // MEDIATIONSESSION_H
