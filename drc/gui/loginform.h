#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>
#include <QKeyEvent>

#include "Mediator.h"

namespace Ui {
class LoginForm;
}

class AsyncMediatorCall;
class MediatorArg;

/*!
 * \brief The LoginForm class
 */
class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    void keyPressEvent(QKeyEvent *pe);

private slots:
    /*!
     * \brief on_loginButton_clicked
     */
    void on_loginButton_clicked();
    /*!
     * \brief on_usernameLineEdit_editingFinished
     */
    void on_usernameLineEdit_editingFinished();
    /*!
     * \brief on_passwordLineEdit_editingFinished
     */
    void on_passwordLineEdit_editingFinished();

private:
    Ui::LoginForm *ui;
    QString _username;
    QString _password;

    AsyncMediatorCall* _asyncAuthenticate;

    MediatorId _mediatorId_authenticateResponse;
    /*!
     * \brief authenticateResponse
     * \param arg
     */
    void authenticateResponse(MediatorArg arg);
};

#endif // LOGINFORM_H
