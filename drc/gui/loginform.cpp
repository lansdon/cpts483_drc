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

    _asyncAuthenticate = new AsyncMediatorCall(
                MKEY_GUI_AUTHENTICATE_USER,
                MKEY_DB_AUTHENTICATE_USER_DONE,
                [this](MediatorArg arg){authenticateResponse(arg);},
                nullptr,
                true,
                1
            );

    ui->statusLabel->setText("Please enter your credentials");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginButton_clicked()
{

    ui->statusLabel->setText("Authenticating...");
    _asyncAuthenticate->GetMediatorArg().SetArg(new User(_username, _password));
    _asyncAuthenticate->Send();

    // TEMPORARY! Set the user object on CurrentUser to trigger a login sequence.
    // This will effectively bypass authenticating with the db until it's implemented.
    // But let us get to the menus and see the gui change post-login.
    CurrentUser::LoginUser(new User(_username, _password));
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
