#ifndef FRUITNAMEFORM_H
#define FRUITNAMEFORM_H

#include <QWidget>
#include "particapants.h"
#include "Mediator.h"
#include "AsyncMediatorCall.h"
#include "DRCModels.h"
#include <vector>
//#include "drc_shared/models/DRCModels.h"


// Forward declarations
class AsyncMediatorCall;
class MediatorArg;

namespace Ui {
class FruitNameForm;
}

class FruitNameForm : public QWidget
{
    Q_OBJECT

public:
    explicit FruitNameForm(QWidget *parent = 0);
    ~FruitNameForm();

private slots:
    void on_retrieveButton_clicked();
    void on_sendButton_clicked();
    void on_nameLineEdit_returnPressed();

    void on_AddParty_clicked();

    void on_removePushButton_clicked();

    // Async Callbacks Must Be SLOTS!?
    void RecieveFruitNameResult(MediatorArg arg);
    void UpdateForm(MediatorArg arg);

private:
    Ui::FruitNameForm *ui;
    QString _name;

    // Misc Functions
    void UpdateNameField(QString str);

    //////////// SEND / RECIEVE EVENTS /////////////////
    AsyncMediatorCall *asyncSendFruitName;
    AsyncMediatorCall *asyncSendSearch;
    void SendSearchName(QString name);
    void SendFruitName(QString name);
    Particapants *claiment;
};

#endif // FRUITNAMEFORM_H

