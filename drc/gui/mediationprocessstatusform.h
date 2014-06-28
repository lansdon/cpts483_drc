#ifndef MEDIATIONPROCESSSTATUSFORM_H
#define MEDIATIONPROCESSSTATUSFORM_H

#include <QWidget>
#include "mediationprocess.h"

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

private slots:
    void on_conflictComboBox_currentIndexChanged(int index);

    void on_statusComboBox_currentIndexChanged(int index);

    void on_countyComboBox_currentIndexChanged(int index);

    void on_referralComboBox_currentIndexChanged(int index);

private:
    Ui::MediationProcessStatusForm *ui;

    MediationProcess* _mediationProcess;

    void Update();

    void ConfigureComboBoxes(); // Sets the values based on enums.
signals:
    void hovered();
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
