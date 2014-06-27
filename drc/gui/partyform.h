#ifndef PARTYFORM_H
#define PARTYFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include "persondetailsform.h"
#include "party.h"
class Party;
class Person;

namespace Ui {
class PartyForm;
}


//enum ObserverTableColumns
//{
//    OCOL_ID = 0,
//    OCOL_NAME,
//    OCOL_ROLE
//};

//enum ChildrenTableColumns
//{
//    CCOL_ID = 0,
//    CCOL_NAME,
//    CCOL_INVOLVED
//};


class PartyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyForm(QWidget *parent = 0, Party* party = nullptr);
    ~PartyForm();
    void setParty(Party *value);
    QString getFullName() const {return _party->GetPrimary()->FullName();}
private slots:
    void DoSaveSignal() { emit SaveSignaled(); }
    void DoEditSignal() { emit EditSignaled(); }
private:
    Ui::PartyForm *ui;
    Party* _party;
    PersonDetailsForm *_personDetailsForm;

signals:
    void SaveSignaled();    // Passes save events to parent
    void EditSignaled();    // Passes edit events to parent
};

#endif // PARTYFORM_H
