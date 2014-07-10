#ifndef MONTHLYREPORTFORM_H
#define MONTHLYREPORTFORM_H

#include <QWidget>

namespace Ui {
class MonthlyReportForm;
}

class MonthlyReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit MonthlyReportForm(QWidget *parent = 0);
    ~MonthlyReportForm();

private:
    Ui::MonthlyReportForm *ui;
};

#endif // MONTHLYREPORTFORM_H
