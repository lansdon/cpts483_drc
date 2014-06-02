#include "loginform.h"
#include "ui_loginform.h"
#include "drc_shared/models/DRCModels.h"
#include "drc_shared/models/User.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/mediator/MediatorKeys.h"
#include <QDebug>


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
                true
            );

    ui->statusLabel->setText("stuff");
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
        ui->statusLabel->setText(QString::fromStdString(arg.ErrorMessage()));
    }
}