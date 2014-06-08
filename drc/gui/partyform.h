#ifndef PARTYFORM_H
#define PARTYFORM_H

#include <QWidget>

class Party;

namespace Ui {
class PartyForm;
}

class PartyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyForm(QWidget *parent = 0, Party* party = nullptr);
    ~PartyForm();

private:
    Ui::PartyForm *ui;

    Party* _party;
};

#endif // PARTYFORM_H
