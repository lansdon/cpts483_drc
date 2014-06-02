#ifndef USERLOGINPROCESSOR_H
#define USERLOGINPROCESSOR_H

#include <string>
#include "../drc_shared/mediator/MediatorArg.h"
#include "../drc_shared/models/User.h"
#include "Processor.h"

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

    User* _user;
    std::string* _userName;

    std::string _requestSalt;
    std::string _sendUser;
};

#endif // USERLOGINPROCESSOR_H
