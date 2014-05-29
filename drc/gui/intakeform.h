#ifndef INTAKEFORM_H
#define INTAKEFORM_H

#include <QWidget>

namespace Ui {
class IntakeForm;
}

class IntakeForm : public QWidget
{
    Q_OBJECT

public:
    explicit IntakeForm(QWidget *parent = 0);
    ~IntakeForm();

private:
    Ui::IntakeForm *ui;
};

#endif // INTAKEFORM_H
