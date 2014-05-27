#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include "gui/IntakeForm.h"
#include <QMainWindow>
#include <QString>

namespace Ui {
class DRCClient;
}

class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

private slots:
    void on_retrieveButton_clicked();

    void on_sendButton_clicked();

    void on_nameLineEdit_returnPressed();

private:
    Ui::DRCClient *ui;
    QString _name;

    void UpdateNameField(QString str);

    //////////// SEND / RECIEVE EVENTS /////////////////
    AsyncMediatorCall *asyncSendFruitName;
    void SendFruitName(QString name);
    void RecieveFruitNameResult(MediatorArg arg);

};

#endif // DRCClient_H
