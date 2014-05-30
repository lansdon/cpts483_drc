#ifndef FRUITNAMEFORM_H
#define FRUITNAMEFORM_H

#include <QWidget>
#include "particapants.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/models/DRCModels.h"
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

private:
    Ui::FruitNameForm *ui;
    QString _name;

    // Misc Functions
    void UpdateNameField(QString str);
    void UpdateForm(MediatorArg arg);

    //////////// SEND / RECIEVE EVENTS /////////////////
    AsyncMediatorCall *asyncSendFruitName;
    AsyncMediatorCall *asyncSendSearch;
    void SendSearchName(QString name);
    void SendFruitName(QString name);
    void RecieveFruitNameResult(MediatorArg arg);
};

#endif // FRUITNAMEFORM_H

