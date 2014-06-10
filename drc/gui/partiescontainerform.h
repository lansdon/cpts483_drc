#ifndef PARTIESCONTAINERFORM_H
#define PARTIESCONTAINERFORM_H

#include <QWidget>

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


private:
    Ui::PartiesContainerForm *ui;

    void SetParty1View(Party* party);
    void SetParty2View(Party* party);

};

#endif // PARTIESCONTAINERFORM_H