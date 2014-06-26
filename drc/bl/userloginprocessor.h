#ifndef USERLOGINPROCESSOR_H
#define USERLOGINPROCESSOR_H

#include <string>
#include "MediatorArg.h"
#include "User.h"

class SHA256_Crypto;

class UserLoginProcessor
{
public:
    UserLoginProcessor(QString authUser, QString sendUser);
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

    void Authenticate(MediatorArg arg);

    ~UserLoginProcessor();
private:
    void ReceiveSalt(MediatorArg arg);
    void CleanUserName();

    QString _sendUser;
    QString _requestSalt;
    User* _user;
    QString* _userName;
};

#endif // USERLOGINPROCESSOR_H
