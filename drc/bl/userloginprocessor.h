#ifndef USERLOGINPROCESSOR_H
#define USERLOGINPROCESSOR_H

#include <string>
#include "MediatorArg.h"
#include "User.h"
#include "Mediator.h"

class SHA256_Crypto;

/*!
 * \brief The UserLoginProcessor class
 */
class UserLoginProcessor
{
public:
    UserLoginProcessor(QString authUser, QString sendUser);
    /*!
     * \brief Process
     * \param arg
     */
    void Process(MediatorArg arg);
    /*!
     * \brief Load
     * \param arg
     */
    void Load(MediatorArg arg);
    /*!
     * \brief Authenticate
     * \param arg
     */
    void Authenticate(MediatorArg arg);

    ~UserLoginProcessor();
private:
    /*!
     * \brief ReceiveSalt
     * \param arg
     */
    void ReceiveSalt(MediatorArg arg);
    /*!
     * \brief CleanUserName
     */
    void CleanUserName();
    MediatorId _unregAurhUserCall;
    QString MKEY;
    QString _sendUser;
    QString _requestSalt;
    User* _user;
    QString* _userName;
};

#endif // USERLOGINPROCESSOR_H
