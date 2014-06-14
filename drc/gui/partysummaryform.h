#ifndef PARTYSUMMARYFORM_H
#define PARTYSUMMARYFORM_H

#include <QWidget>

class Party;

namespace Ui {
class PartySummaryForm;
}

class PartySummaryForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartySummaryForm(QWidget *parent = 0, Party* party = nullptr);
    ~PartySummaryForm();

private:
    Ui::PartySummaryForm *ui;

    Party* _party;
};

#endif // PARTYSUMMARYFORM_H
