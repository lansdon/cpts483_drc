#ifndef FRUITNAMEFORM_H
#define FRUITNAMEFORM_H

#include <QWidget>

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

private:
    Ui::FruitNameForm *ui;
    QString _name;

    // Misc Functions
    void UpdateNameField(QString str);

    //////////// SEND / RECIEVE EVENTS /////////////////
    AsyncMediatorCall *asyncSendFruitName;
    void SendFruitName(QString name);
    void RecieveFruitNameResult(MediatorArg arg);
};

#endif // FRUITNAMEFORM_H

