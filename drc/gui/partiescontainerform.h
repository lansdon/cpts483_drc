#ifndef PARTIESCONTAINERFORM_H
#define PARTIESCONTAINERFORM_H

#include <QWidget>
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


private:
    Ui::PartiesContainerForm *ui;

    void AddPartyTabs(PartyVector* parties);

};

#endif // PARTIESCONTAINERFORM_H
