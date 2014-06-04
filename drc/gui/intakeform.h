#ifndef INTAKEFORM_H
#define INTAKEFORM_H

#include <QWidget>
#include "Intake.h"

namespace Ui {
class IntakeForm;
}

class IntakeForm : public QWidget
{
    Q_OBJECT

public:
    explicit IntakeForm(QWidget *parent = 0);
    ~IntakeForm();

private slots:
    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::IntakeForm *ui;

    // Current Intake Object
    Intake _currentIntake;

    //////////// Async handlers /////////////////
    AsyncMediatorCall *_asyncSaveIntake;
    AsyncMediatorCall *_asyncLoadIntake;

    // Save Intake Form Callback (result)
    void Recieve_SaveIntakeForm(MediatorArg arg);

    // Load Intake Form Callback (result)
    void Recieve_LoadIntakeForm(MediatorArg arg);
};

#endif // INTAKEFORM_H
