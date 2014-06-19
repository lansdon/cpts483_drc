#ifndef MEDIATIONPROCESSTABLEFORM_H
#define MEDIATIONPROCESSTABLEFORM_H

#include <QWidget>
#include "drctypes.h"
#include <vector>

enum MediationTableSortTypes
{
    MEDIATION_SORT_T_NONE,
    MEDIATION_SORT_T_PENDING,
    MEDIATION_SORT_T_RECENT,
    MEDIATION_SORT_T_SCHEDULED,
    MEDIATION_SORT_T_CLOSED
};

namespace Ui {
class MediationProcessTableForm;
}

class MediationProcessTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessTableForm(QWidget *parent = 0, MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    ~MediationProcessTableForm();

private slots:
    void on_recentButton_clicked();

    void on_pendingButton_clicked();

    void on_scheduledButton_clicked();

    void on_closedButton_clicked();

private:
    Ui::MediationProcessTableForm *ui;

    MediationProcessVector _mediationsVector;

    void ConfigMediationProcecssViewTable();
    void PopulateMediationProcessTable();

    void LoadTableData(MediationTableSortTypes sortType);
    void MakeSampleTable();
};

#endif // MEDIATIONPROCESSTABLEFORM_H
