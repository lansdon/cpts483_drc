#ifndef SEARCHWIZARDSELECTTYPE_H
#define SEARCHWIZARDSELECTTYPE_H

#include <QWizard>
#include <QLabel>
#include <QComboBox>


class SearchWizardSelectType : public QWizardPage
{
     Q_OBJECT

 public:
     SearchWizardSelectType(QWidget *parent = 0);

 private:
     QLabel *searchTypeLabel;
     QComboBox *searchTypeComboBox;

     QString _searchType;

public slots:
    void handleSelectionChanged(int index);

};

#endif // SEARCHWIZARDSELECTTYPE_H
