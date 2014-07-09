#ifndef RESWAREPORTFORM_H
#define RESWAREPORTFORM_H

#include <QWidget>
#include <QTextDocument>
#include "MediatorArg.h"

namespace Ui {
class ResWaReportForm;
}

class ResWaReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResWaReportForm(QWidget *parent = 0);
    ~ResWaReportForm();

private slots:

    void on_showResportBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::ResWaReportForm *ui;

    QTextDocument* _report;

    void BuildReport();

    void RecieveReport(MediatorArg arg);
};

#endif // RESWAREPORTFORM_H
