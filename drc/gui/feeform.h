#ifndef FEEFORM_H
#define FEEFORM_H

#include <QWidget>

namespace Ui {
class FeeForm;
}

class FeeForm : public QWidget
{
    Q_OBJECT

public:
    explicit FeeForm(QWidget *parent = 0);
    ~FeeForm();

private:
    Ui::FeeForm *ui;
};

#endif // FEEFORM_H
