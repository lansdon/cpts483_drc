#ifndef MEDIATIONPROCESSSTATUSFORM_H
#define MEDIATIONPROCESSSTATUSFORM_H

#include <QWidget>
#include "mediationprocess.h"
#include "Mediator.h"
#include "MediatorKeys.h"

namespace Ui {
class MediationProcessStatusForm;
}

class MediationProcessStatusForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessStatusForm(QWidget *parent = 0, MediationProcess* mediationProcess = nullptr);
    ~MediationProcessStatusForm();

    void setMediationProcess(MediationProcess* value);
    void SetStatusLabel(QString message, bool isError = false);
    void SetSavedLabel(bool isSaved);

private slots:
    void on_conflictComboBox_currentIndexChanged(int index);

    void on_statusComboBox_currentIndexChanged(int index);

    void on_countyComboBox_currentIndexChanged(int index);

    void on_referralComboBox_currentIndexChanged(int index);

    void on_courtCheckBox_clicked();

    void on_courtTypeComboBox_currentIndexChanged(int index);

    void on_courDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_courtOrderComboBox_currentIndexChanged(int index);

    void on_expirationDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_inquiryTypeComboBox_currentIndexChanged(int index);

    void on_infoOnlyCheckBox_toggled(bool checked);

    void on_spanishCheckBox_clicked(bool checked);

    void on_regularRadioButton_clicked();

    void on_facilitationRadioButton_clicked();

    void on_phoneRadioButton_clicked();

    void on_mediationClauseCheckBox_toggled(bool checked);

    void on_coachingRadioButton_clicked();

    void on_courtOrderLineEdit_textEdited(const QString &arg1);

private:
    Ui::MediationProcessStatusForm *ui;

    MediationProcess* _mediationProcess;

    void Update();

    void ConfigureComboBoxes(); // Sets the values based on enums.

    void MPSaveFinished(MediatorArg arg);
    void sessionTypeDisplay();
    void updateSessionType();

    MediatorId _SavePendingCallbackId;      // use to unregister callbacks
    MediatorId _PersistMPDoneCallbackId;    // use to unregister callbacks
    MediatorId _LoadMPCallbackId;           // use to unregister callbacks

signals:
    void hovered();
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
