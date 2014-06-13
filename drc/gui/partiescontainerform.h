#ifndef PARTIESCONTAINERFORM_H
#define PARTIESCONTAINERFORM_H

#include <QWidget>
#include "partyform.h"

class Party;

namespace Ui {
class PartiesContainerForm;
}

class PartiesContainerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartiesContainerForm(QWidget *parent = 0, Party* party1 = nullptr, Party* party2 = nullptr);
    ~PartiesContainerForm();
    void SetParty1View(Party* party);
    void SetParty2View(Party* party);

private:
    Ui::PartiesContainerForm *ui;
    PartyForm *p1;
    PartyForm *p2;

};

#endif // PARTIESCONTAINERFORM_H
