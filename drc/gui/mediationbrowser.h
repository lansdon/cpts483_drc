#ifndef MEDIATIONPROCESSTABLEFORM_H
#define MEDIATIONPROCESSTABLEFORM_H

#include <QWidget>
#include "drctypes.h"
#include <vector>
#include "Mediator.h"



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
    void Refresh();
private slots:
    void on_recentButton_clicked();

    void on_pendingButton_clicked();

    void on_scheduledButton_clicked();

    void on_closedButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_searchBtn_clicked();

signals:

    void on_mediationProcessSelected(MediationProcess* process);

private:
    Ui::MediationBrowser *ui;

    MediationProcessVector _mediationsVector;
    MediationTableSortTypes _sortType;

    void ConfigMediationProcecssViewTable();
    void PopulateMediationProcessTable();

    void MakeSampleTable();
    void OnRecieveMediationVector(MediatorArg arg);

    MediatorId _requestRecentCallback;
    MediatorId _setMediationsCallback;
    MediatorId _refreshMediationsCallback;
    MediatorId _queryMediationCallback;
};

#endif // MEDIATIONPROCESSTABLEFORM_H
