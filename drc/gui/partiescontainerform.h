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

    void AddPartyTabs(PartyVector* parties);
private slots:
    void DoSaveSignal() { emit SaveSignaled(); }
    void DoEditSignal() { emit EditSignaled(); }
private:
    Ui::PartiesContainerForm *ui;
//    std::vector<PartyForm*> PartyFormVector;
signals:
    void SaveSignaled();    // Passes save events to parent
    void EditSignaled();    // Passes edit events to parent

};

#endif // PARTIESCONTAINERFORM_H
