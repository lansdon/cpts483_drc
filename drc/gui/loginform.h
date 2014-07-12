#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>
#include <QKeyEvent>

#include "Mediator.h"

namespace Ui {
class LoginForm;
}

class AsyncMediatorCall;
class MediatorArg;

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    void keyPressEvent(QKeyEvent *pe);

private slots:
    void on_loginButton_clicked();

    void on_usernameLineEdit_editingFinished();

    void on_passwordLineEdit_editingFinished();

private:
    Ui::LoginForm *ui;
    QString _username;
    QString _password;

    AsyncMediatorCall* _asyncAuthenticate;

    MediatorId _mediatorId_authenticateResponse;
    void authenticateResponse(MediatorArg arg);
};

#endif // LOGINFORM_H
