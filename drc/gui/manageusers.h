#ifndef MANAGEUSERS_H
#define MANAGEUSERS_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include "User.h"
#include "Mediator.h"
#include "MediatorKeys.h"

namespace Ui {
class ManageUsers;
}

class ManageUsers : public QWidget
{
    Q_OBJECT

public:
    explicit ManageUsers(QWidget *parent = 0);
    ~ManageUsers();

private slots:
    void on_AddUserButton_clicked();

    void on_DeleteUserButton_clicked();

    void on_usernameLineEdit_editingFinished();

    void on_passwordLineEdit_editingFinished();

    void on_reenterpasswordLineEdit_editingFinished();

    void on_reenterpasswordLineEdit_textChanged(const QString &arg1);

    void on_IsAdminBox_toggled(bool checked);

    void on_usertableWidget_doubleClicked(const QModelIndex &index);

    void on_UpdateUserButton_clicked();

private:
    Ui::ManageUsers *ui;

    QString _username;
    QString _password;
    QString _reenteredpassword;

    MediatorId _mediatorId_VerifyAddUser;
    MediatorId _mediatorId_VerifyUpdateUser;
    MediatorId _mediatorId_VerifyRemoveUser;
    MediatorId _mediatorId_GetAllUsers;

    bool _admin;

    bool _passwordMatch;

    User* _selectedUser;

    QVector<User*>* _userVector;

    void GetAllUsers(MediatorArg arg);

    void VerifyDeleteUser(MediatorArg arg);

    void VerifyAddNewUser(MediatorArg arg);

    void VerifyUpdateUser(MediatorArg arg);

    void ConfigureUserTableView();

    void PopulateUserTableView();
};

#endif // MANAGEUSERS_H
