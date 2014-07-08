#ifndef RESWAREPORTFORM_H
#define RESWAREPORTFORM_H

#include <QWidget>
#include <QTextDocument>

namespace Ui {
class ResWaReportForm;
}

class ResWaReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResWaReportForm(QWidget *parent = 0);
    ~ResWaReportForm();

private:
    Ui::ResWaReportForm *ui;

    QTextDocument* _report;

    void BuildReport();
};

#endif // RESWAREPORTFORM_H
