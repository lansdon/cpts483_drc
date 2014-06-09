#ifndef PARTYFORM_H
#define PARTYFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>

class Party;
class Person;

namespace Ui {
class PartyForm;
}


enum ObserverTableColumns
{
    OCOL_ID = 0,
    OCOL_NAME,
    OCOL_ROLE
};

enum ChildrenTableColumns
{
    CCOL_ID = 0,
    CCOL_NAME,
    CCOL_INVOLVED
};


class PartyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyForm(QWidget *parent = 0, Party* party = nullptr);
    ~PartyForm();

private slots:
    void ObserverCellSelected(int nRow, int nCol);
    void ChildCellSelected(int nRow, int nCol);
    void ObserverChanged(Person* p);
    void ObserverDeleted(Person* p);
    void ChildChanged(Person* p);
    void ChildDeleted(Person* p);

private:
    Ui::PartyForm *ui;

    Party* _party;

    QTableWidget* _observerTable;
    QStringList _observerTableHeader;
    QTableWidget* _childrenTable;
    QStringList _childrenTableHeader;

    void ConfigObserverTable();
    void PopulateObserverTable();
    void ConfigChildrenTable();
    void PopulateChildrenTable();
};

#endif // PARTYFORM_H
