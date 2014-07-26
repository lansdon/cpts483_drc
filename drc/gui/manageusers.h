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

/*!
 * \brief The ManageUsers class
 */
class ManageUsers : public QWidget
{
    Q_OBJECT

public:
    explicit ManageUsers(QWidget *parent = 0);
    ~ManageUsers();

private slots:
    /*!
     * \brief on_AddUserButton_clicked
     */
    void on_AddUserButton_clicked();
    /*!
     * \brief on_DeleteUserButton_clicked
     */
    void on_DeleteUserButton_clicked();
    /*!
     * \brief on_usernameLineEdit_editingFinished
     */
    void on_usernameLineEdit_editingFinished();
    /*!
     * \brief on_passwordLineEdit_editingFinished
     */
    void on_passwordLineEdit_editingFinished();
    /*!
     * \brief on_reenterpasswordLineEdit_editingFinished
     */
    void on_reenterpasswordLineEdit_editingFinished();
    /*!
     * \brief on_reenterpasswordLineEdit_textChanged
     * \param arg1
     */
    void on_reenterpasswordLineEdit_textChanged(const QString &arg1);
    /*!
     * \brief on_IsAdminBox_toggled
     * \param checked
     */
    void on_IsAdminBox_toggled(bool checked);
    /*!
     * \brief on_usertableWidget_doubleClicked
     * \param index
     */
    void on_usertableWidget_doubleClicked(const QModelIndex &index);
    /*!
     * \brief on_UpdateUserButton_clicked
     */
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
    /*!
     * \brief GetAllUsers
     * \param arg
     */
    void GetAllUsers(MediatorArg arg);
    /*!
     * \brief VerifyDeleteUser
     * \param arg
     */
    void VerifyDeleteUser(MediatorArg arg);
    /*!
     * \brief VerifyAddNewUser
     * \param arg
     */
    void VerifyAddNewUser(MediatorArg arg);
    /*!
     * \brief VerifyUpdateUser
     * \param arg
     */
    void VerifyUpdateUser(MediatorArg arg);
    /*!
     * \brief ConfigureUserTableView
     */
    void ConfigureUserTableView();
    /*!
     * \brief PopulateUserTableView
     */
    void PopulateUserTableView();
};

#endif // MANAGEUSERS_H
