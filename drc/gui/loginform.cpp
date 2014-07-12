#include "loginform.h"
#include "ui_loginform.h"
#include "DRCModels.h"
#include "User.h"
#include "AsyncMediatorCall.h"
#include "MediatorKeys.h"
#include <QDebug>
#include "CurrentUser.h"



LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    CurrentUser::Init();

    _mediatorId_authenticateResponse = Mediator::Register(MKEY_DB_AUTHENTICATE_USER_DONE, [this](MediatorArg arg){authenticateResponse(arg);});

    ui->statusLabel->setText("Please enter your credentials");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->groupBox->setStyleSheet("QGroupBox {\
                                border: 2px solid gray;\
                                border-radius: 5px;\
                                margin-top: 1.3em;\
                                } QGroupBox::title { subcontrol-origin: margin;\
                                subcontrol-position: top left;\
                                padding:0 3px;\
                                }");
}

void LoginForm::keyPressEvent(QKeyEvent *pe)
{
    if(pe->key() == Qt::Key_Return) on_loginButton_clicked();
}

LoginForm::~LoginForm()
{
    delete ui;
    Mediator::Unregister(MKEY_DB_AUTHENTICATE_USER_DONE, _mediatorId_authenticateResponse);
}

void LoginForm::on_loginButton_clicked()
{

    ui->statusLabel->setText("Authenticating...");

    MediatorArg arg;
    arg.SetSuccessful(true);
    User *user = new User(_username, _password);
    arg.SetArg(user);

    Mediator::Call(MKEY_GUI_AUTHENTICATE_USER, arg);
}

void LoginForm::authenticateResponse(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        user = arg.getArg<User*>();
        if(user)
        {
            // SUCCESS
            qDebug() << "Authentication successful!";
            ui->statusLabel->setText("Authentication successful!");
            Mediator::Call(MKEY_CURRENT_USER_CHANGED, arg);
        }
        else
        {
            // Set the error label
            ui->statusLabel->setText("Invalid argument from db.");
        }
    }
    else
    {
        // Set the error label.
        ui->statusLabel->setText("Authentication failed!");
        _username.clear();
        _password.clear();
        ui->usernameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->usernameLineEdit->setFocus();
    }
}

void LoginForm::on_usernameLineEdit_editingFinished()
{
    _username = ui->usernameLineEdit->text();
}

void LoginForm::on_passwordLineEdit_editingFinished()
{
    _password = ui->passwordLineEdit->text();
}
