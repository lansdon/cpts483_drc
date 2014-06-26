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
    void on_notesToggleBtn_clicked();

    void on_Last10Label_linkHovered(const QString &link);

private:
    Ui::MediationProcessStatusForm *ui;

    MediationProcess* _mediationProcess;

    void Update();

    void ConfigureComboBoxes(); // Sets the values based on enums.
signals:
    void hovered();
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
