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
        ui->statusLabel->setText(arg.ErrorMessage());
    }
}
