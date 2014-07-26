#ifndef MEDIATIONPROCESSTABLEFORM_H
#define MEDIATIONPROCESSTABLEFORM_H

#include <QWidget>
#include "drctypes.h"
#include <vector>
#include "Mediator.h"

namespace Ui {
class MediationBrowser;
}

/*!
 * \brief The MediationBrowser class
 */
class MediationBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit MediationBrowser(QWidget *parent = 0, MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    ~MediationBrowser();
    /*!
     * \brief LoadTableData
     * \param sortType
     */
    void LoadTableData(MediationTableSortTypes sortType);
    /*!
     * \brief Refresh
     */
    void Refresh();
private slots:
    /*!
     * \brief on_recentButton_clicked
     */
    void on_recentButton_clicked();
    /*!
     * \brief on_pendingButton_clicked
     */
    void on_pendingButton_clicked();
    /*!
     * \brief on_scheduledButton_clicked
     */
    void on_scheduledButton_clicked();
    /*!
     * \brief on_closedButton_clicked
     */
    void on_closedButton_clicked();
    /*!
     * \brief on_tableWidget_doubleClicked
     * \param index
     */
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    /*!
     * \brief on_searchBtn_clicked
     */
    void on_searchBtn_clicked();

signals:
    /*!
     * \brief on_mediationProcessSelected
     * \param process
     */
    void on_mediationProcessSelected(MediationProcess* process);

private:
    Ui::MediationBrowser *ui;

    MediationProcessVector _mediationsVector;
    MediationTableSortTypes _sortType;

    /*!
     * \brief ConfigMediationProcecssViewTable
     */
    void ConfigMediationProcecssViewTable();
    /*!
     * \brief PopulateMediationProcessTable
     */
    void PopulateMediationProcessTable();
    /*!
     * \brief MakeSampleTable
     */
    void MakeSampleTable();
    /*!
     * \brief OnRecieveMediationVector
     * \param arg
     */
    void OnRecieveMediationVector(MediatorArg arg);

    MediatorId _requestRecentCallback;
    MediatorId _requestPendingCallback;
    MediatorId _requestScheduledCallback;
    MediatorId _requestClosedCallback;
    MediatorId _setMediationsCallback;
    MediatorId _refreshMediationsCallback;
    MediatorId _queryMediationCallback;
};

#endif // MEDIATIONPROCESSTABLEFORM_H
