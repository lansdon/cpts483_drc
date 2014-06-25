#ifndef MEDIATIONSESSIONFORM_H
#define MEDIATIONSESSIONFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include <vector>
#include "drc_shared/models/mediationprocess.h"
#include "drc_shared/drctypes.h"
#include "mediator.h"


namespace Ui {
class MediationSessionForm;
}

class MediationSessionForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSessionForm(QWidget *parent = 0, MediationSession * MSC = nullptr);
    ~MediationSessionForm();
    void setParties(int input);
    void updateTabs(std::vector<Person *> *input);
    void setMediationSession(MediationSession *value);

private slots:
    void on_CancelledRadioButton_toggled(bool checked);

    void on_PendingRadioButton_toggled(bool checked);

    void on_confirmedRadioButton_toggled(bool checked);

    void on_rescheduledRadioButton_toggled(bool checked);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_Fee1LineEdit_editingFinished();

    void on_Fee1PaidCheckBox_toggled(bool checked);

    void on_Fee2LineEdit_editingFinished();

    void on_FamilyFeeLineEdit_editingFinished();

    void on_OtherFeeLineEdit_editingFinished();

    void on_Fee2PaidCheckBox_toggled(bool checked);

    void on_FamilyFeePaidCheckBox_toggled(bool checked);

    void on_OtherFeePaidCheckBox_toggled(bool checked);

    void on_incomeFee1LineEdit_editingFinished();

    void on_incomeFee2LineEdit_editingFinished();

    void on_incomeFeeFamilyLineEdit_editingFinished();

    void on_incomeFeeOtherLineEdit_editingFinished();

    void on_mediator1EditPushButton_clicked();

    void on_mediator2EditPushButton_clicked();

    void on_observer1EditPushButton_clicked();

    void on_observer2EditPushButton_clicked();

    void deletePersonContact(Person *value);

    void savePersonContact(Person *value);

    void SaveSignaled();
    void EditSignaled();

    void SetSessionEvent(MediatorArg arg);
private:
    Ui::MediationSessionForm *ui;
    MediationSession *_mediationSession;

    void fillFields(MediationSession *input);
    bool FillingFields;

};

#endif // MEDIATIONSESSIONFORM_H
