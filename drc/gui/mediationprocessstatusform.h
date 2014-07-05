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

    void on_shuttleCheckBox_clicked();

    void on_courtTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_courDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_courtOrderComboBox_currentIndexChanged(int index);

    void on_expirationDateTimeEdit_windowIconChanged(const QIcon &icon);

private:
    Ui::MediationProcessStatusForm *ui;

    MediationProcess* _mediationProcess;

    void Update();

    void ConfigureComboBoxes(); // Sets the values based on enums.

    void MPSaveFinished(MediatorArg arg);

    MediatorId _SavePendingCallbackId;      // use to unregister callbacks
    MediatorId _PersistMPDoneCallbackId;    // use to unregister callbacks

signals:
    void hovered();
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
