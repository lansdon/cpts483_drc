#ifndef USERLOGINPROCESSOR_H
#define USERLOGINPROCESSOR_H

#include <string>
//#include "Crypto/SHA256_Crypto.h"
#include "MediatorArg.h"
#include "User.h"
#include "Processor.h"

class SHA256_Crypto;

class UserLoginProcessor: Processor
{
public:
    UserLoginProcessor(std::string authUser, std::string sendUser,
                       std::string requestSalt, std::string receiveSalt);
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

    void Authenticate(MediatorArg arg);

    ~UserLoginProcessor();
private:
    void ReceiveSalt(MediatorArg arg);
    void CleanUserName();

    std::string _sendUser;
    std::string _requestSalt;
    User* _user;
    std::string* _userName;
};

#endif // USERLOGINPROCESSOR_H
