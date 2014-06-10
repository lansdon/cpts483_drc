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

class QueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryForm(QWidget *parent = 0);
    ~QueryForm();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_searchButton_clicked();

    void RecievedPersonResult(MediatorArg arg);
    void RecievedMediationResult(MediatorArg arg);

public slots:
     void ResultCellSelected(int nRow, int nCol);

private:
    Ui::QueryForm *ui;

    SearchTypes _searchType;

    QWidget* _currentInputForm;
    void ConfigureInputForm();

    // Results Table
    QTableWidget* _resultsTable;
    QStringList _resultsTableHeader;
    void ConfigResultsTable();
    void PopulateResultsTable();

    // Async Calls to DB
    AsyncMediatorCall* _asyncQueryPerson;
    AsyncMediatorCall* _asyncQueryMediation;

    PersonVector* _personResults;
    MediationProcessVector* _mediationResults;
};

#endif // QUERYFORM_H
