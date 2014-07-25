#ifndef QUERYFORM_H
#define QUERYFORM_H

#include <QWidget>
#include "persondetailsform.h"
#include <QTableWidget>
#include "drctypes.h"
#include "AsyncMediatorCall.h"


namespace Ui {
class QueryForm;
}

/*!
 * \brief The QueryForm class
 */
class QueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryForm(QWidget *parent = 0);
    ~QueryForm();

private slots:
    /*!
     * \brief on_comboBox_currentIndexChanged
     * \param arg1
     */
    void on_comboBox_currentIndexChanged(const QString &arg1);
    /*!
     * \brief on_searchButton_clicked
     */
    void on_searchButton_clicked();
    /*!
     * \brief RecievedPersonResult
     * \param arg
     */
    void RecievedPersonResult(MediatorArg arg);
    /*!
     * \brief RecievedMediationResult
     * \param arg
     */
    void RecievedMediationResult(MediatorArg arg);

public slots:
    /*!
     * \brief ResultCellSelected
     * \param nRow
     * \param nCol
     */
    void ResultCellSelected(int nRow, int nCol);
    /*!
     * \brief NewMediationSearchSelected
     */
    void NewMediationSearchSelected();
    /*!
     * \brief NewPersonSearchSelected
     */
    void NewPersonSearchSelected();

private:
    Ui::QueryForm *ui;

    SearchTypes _searchType;

    QWidget* _currentInputForm;
    /*!
     * \brief ConfigureInputForm
     */
    void ConfigureInputForm();

    // Results Table
    QTableWidget* _resultsTable;
    QStringList _resultsTableHeader;
    /*!
     * \brief ConfigResultsTable
     */
    void ConfigResultsTable();
    /*!
     * \brief PopulateResultsTable
     */
    void PopulateResultsTable();

    // Async Calls to DB
    AsyncMediatorCall* _asyncQueryPerson;
    AsyncMediatorCall* _asyncQueryMediation;

    PersonVector* _personResults;
    MediationProcessVector* _mediationResults;
    /*!
     * \brief ConfigureToolbar
     */
    void ConfigureToolbar();
};

#endif // QUERYFORM_H
