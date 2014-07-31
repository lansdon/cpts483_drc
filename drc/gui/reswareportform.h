#ifndef RESWAREPORTFORM_H
#define RESWAREPORTFORM_H

#include <QWidget>
#include <QTextDocument>
#include "MediatorArg.h"
#include "Mediator.h"

namespace Ui {
class ResWaReportForm;
}

/*!
 * \brief The ResWaReportForm class
 */
class ResWaReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResWaReportForm(QWidget *parent = 0);
    ~ResWaReportForm();

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
    Ui::ResWaReportForm *ui;
    MediatorId _unregMediatorReportDoneCall;

    QTextDocument* _report;
    /*!
     * \brief RecieveReport
     * \param arg
     */
    void RecieveReport(MediatorArg arg);
};

#endif // RESWAREPORTFORM_H
