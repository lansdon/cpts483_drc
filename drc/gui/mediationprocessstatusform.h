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

private:
    Ui::MediationProcessStatusForm *ui;

    MediationProcess* _mediationProcess;

    void Update();

    void ConfigureComboBoxes(); // Sets the values based on enums.
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
