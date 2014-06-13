#ifndef PARTIESCONTAINERFORM_H
#define PARTIESCONTAINERFORM_H

#include <QWidget>
#include "partyform.h"
#include "drctypes.h"

class Party;

namespace Ui {
class PartiesContainerForm;
}

class PartiesContainerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartiesContainerForm(QWidget *parent = 0, PartyVector* parties = nullptr);
    ~PartiesContainerForm();
    void SetParty1View(Party* party);
    void SetParty2View(Party* party);

private:
    Ui::PartiesContainerForm *ui;
    PartyForm *p1;
    PartyForm *p2;


    void AddPartyTabs(PartyVector* parties);

};

#endif // PARTIESCONTAINERFORM_H
