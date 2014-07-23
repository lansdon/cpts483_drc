#ifndef MONTHLYREPORTFORM_H
#define MONTHLYREPORTFORM_H

#include <QWidget>
#include "MediatorArg.h"
#include "monthlyreport.h"

namespace Ui {
class MonthlyReportForm;
}

class MonthlyReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit MonthlyReportForm(QWidget *parent = 0);
    ~MonthlyReportForm();

private slots:
    void on_showResportBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::MonthlyReportForm *ui;

    void RecieveReport(MediatorArg arg);

};

#endif // MONTHLYREPORTFORM_H
