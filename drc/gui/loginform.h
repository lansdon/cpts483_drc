#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

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

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginForm *ui;
    std::string _username;
    std::string _password;

    AsyncMediatorCall* _asyncAuthenticate;
    void authenticateResponse(MediatorArg arg);
};

#endif // LOGINFORM_H
