#ifndef MONTHLYREPORTFORM_H
#define MONTHLYREPORTFORM_H

#include <QWidget>
#include "MediatorArg.h"
#include "monthlyreport.h"
#include "Mediator.h"

namespace Ui {
class MonthlyReportForm;
}

/*!
 * \brief The MonthlyReportForm class
 */
class MonthlyReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit MonthlyReportForm(QWidget *parent = 0);
    ~MonthlyReportForm();

private slots:
    /*!
     * \brief on_showResportBtn_clicked
     */
    void on_showResportBtn_clicked();
    /*!
     * \brief on_cancelBtn_clicked
     */
    void on_cancelBtn_clicked();

private:
    Ui::MonthlyReportForm *ui;
    MediatorId _unregMonthlyRequestDoneCall;
    /*!
     * \brief RecieveReport
     * \param arg
     */
    void RecieveReport(MediatorArg arg);

};

#endif // MONTHLYREPORTFORM_H
