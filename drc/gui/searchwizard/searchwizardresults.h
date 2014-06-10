#ifndef SEARCHWIZARDRESULTS_H
#define SEARCHWIZARDRESULTS_H

#include <QTableWidget>
#include <QStringList>
#include <QWizardPage>

class SearchWizardResults : public QWizardPage
 {
     Q_OBJECT

 public:
     SearchWizardResults(QWidget *parent = 0);

 protected:
     void initializePage();

public slots:
     void ResultCellSelected(int nRow, int nCol);

 private:
    QTableWidget* _resultTable;
    QStringList _resultTableHeader;

    int _searchType;

    void ConfigResultsTable();
    void PopulateResultsTable();



 };
#endif // SEARCHWIZARDRESULTS_H
