#ifndef MEDIATIONPROCESSTABLEFORM_H
#define MEDIATIONPROCESSTABLEFORM_H

#include <QWidget>
#include "drctypes.h"
#include <vector>



namespace Ui {
class MediationBrowser;
}

class MediationBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit MediationBrowser(QWidget *parent = 0, MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    ~MediationBrowser();

    void LoadTableData(MediationTableSortTypes sortType);

private slots:
    void on_recentButton_clicked();

    void on_pendingButton_clicked();

    void on_scheduledButton_clicked();

    void on_closedButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

signals:

    void on_mediationProcessSelected(MediationProcess* process);

private:
    Ui::MediationBrowser *ui;

    MediationProcessVector _mediationsVector;

    void ConfigMediationProcecssViewTable();
    void PopulateMediationProcessTable();

    void MakeSampleTable();
};

#endif // MEDIATIONPROCESSTABLEFORM_H