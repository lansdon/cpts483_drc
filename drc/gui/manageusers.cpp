#include "manageusers.h"
#include "ui_manageusers.h"

ManageUsers::ManageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageUsers)
{
    ui->setupUi(this);
}

ManageUsers::~ManageUsers()
{
    delete ui;
}

void ManageUsers::on_AddUserButton_clicked()
{

}

void ManageUsers::on_DeleteUserButton_clicked()
{
    if (_password == _reenteredpassword && _username != "")
    {
        User* newUser = new User();
        newUser->SetName(_username);
        newUser->SetPassword(_password);
        if (ui->IsAdminBox->isChecked())
        {
            newUser->SetType(USER_T_ADMIN);
        }
        else
        {
            newUser->SetType(USER_T_NORMAL);
        }
        MediatorArg arg;
        arg.SetArg(newUser);
        Mediator::Call(MKEY_DB_ADD_NEW_USER, arg);
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
