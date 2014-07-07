#ifndef MANAGEUSERS_H
#define MANAGEUSERS_H

#include <QWidget>
#include <QString>
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

private:
    Ui::ManageUsers *ui;

    QString _username;
    QString _password;
    QString _reenteredpassword;

    bool _admin;

    bool _passwordMatch;

    User* _selectedUser;

    QVector<User>* _userVector;

    void GetAllUsers(MediatorArg arg);

    void ConfigureUserTableView();
};

#endif // MANAGEUSERS_H
