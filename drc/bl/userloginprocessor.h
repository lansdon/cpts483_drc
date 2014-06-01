#ifndef USERLOGINPROCESSOR_H
#define USERLOGINPROCESSOR_H

#include <string>
#include "Processor.h"
#include "../drc_shared/models/User.h"

class UserLoginProcessor : public Processor
{
public:
    UserLoginProcessor(std::string regProcess, std::string sendProcess,
                       std::string regLoad,    std::string sendLoad);
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);
private:
    bool ValidateUser(const User& user, std::string& errorMessage) const;
    bool ValidateUserName(std::string userName, std::string& errorMessage) const;
    bool ValidatePassword(std::string password, std::string& errorMessage) const;
    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // USERLOGINPROCESSOR_H
