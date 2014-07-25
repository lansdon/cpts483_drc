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

/*!
 * \brief The PartyForm class
 */
class PartyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyForm(QWidget *parent = 0, Party* party = nullptr);
    ~PartyForm();
    /*!
     * \brief setParty
     * \param value
     */
    void setParty(Party *value);
    /*!
     * \brief GetParty
     * \return
     */
    Party* GetParty() { return _party; }
    /*!
     * \brief getFullName
     * \return
     */
    QString getFullName() const {return _party->GetPrimary()->FullName();}

private slots:
    /*!
     * \brief DoSaveSignal
     */
    void DoSaveSignal() { emit SaveSignaled(); }
    /*!
     * \brief DoEditSignal
     */
    void DoEditSignal() { emit EditSignaled(); }
private:
    Ui::PartyForm *ui;
    Party* _party;
    PersonDetailsForm *_personDetailsForm;

signals:
    /*!
     * \brief SaveSignaled
     */
    void SaveSignaled();    // Passes save events to parent
    /*!
     * \brief EditSignaled
     */
    void EditSignaled();    // Passes edit events to parent
};

#endif // PARTYFORM_H
