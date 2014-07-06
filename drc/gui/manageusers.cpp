#include "manageusers.h"
#include "ui_manageusers.h"

// Temp
#include <iostream>

ManageUsers::ManageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageUsers)
{
    ui->setupUi(this);

    _admin = false;

    _selectedUser = nullptr;

    // Make it so the passwords entered can't be seen.
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->reenterpasswordLineEdit->setEchoMode(QLineEdit::Password);
}

ManageUsers::~ManageUsers()
{
    delete ui;
}

void ManageUsers::on_AddUserButton_clicked()
{
    if (_passwordMatch && _username != "" && _password != "")
    {
        User *newUser = new User();
        newUser->SetName(_username);
        newUser->SetPassword(_password);
        newUser->SetType((_admin == true ? USER_T_ADMIN : USER_T_NORMAL));
        _selectedUser = newUser;

        MediatorArg arg;
        arg.SetArg(newUser);
        Mediator::Call(MKEY_DB_ADD_NEW_USER, arg);
    }
}

void ManageUsers::on_DeleteUserButton_clicked()
{
    if (_selectedUser != nullptr)
    {
        MediatorArg arg;
        arg.SetArg(_selectedUser);
        Mediator::Call(MKEY_DB_REMOVE_USER, arg);
    }
}

void ManageUsers::on_usernameLineEdit_editingFinished()
{
    _username = ui->usernameLineEdit->text();
}

void ManageUsers::on_passwordLineEdit_editingFinished()
{
    _password = ui->passwordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_editingFinished()
{
    _reenteredpassword = ui->reenterpasswordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_textChanged(const QString &arg1)
{
    if (arg1 != _password)
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : red}");
        ui->MatchingPasswordLabel->setText("No Match!!");

        _passwordMatch = false;
    }
    else
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : green}");
        ui->MatchingPasswordLabel->setText("Match!");

        _passwordMatch = true;
    }
}

void ManageUsers::on_IsAdminBox_toggled(bool checked)
{
    _admin = checked;
}
