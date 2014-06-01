#include "userloginprocessor.h"
#include "../drc_shared/mediator/Mediator.h"

#include <qstring.h>
#include <qdebug.h>

UserLoginProcessor::UserLoginProcessor(std::string regProcess="", std::string sendProcess="",
                           std::string regLoad="", std::string sendLoad="")
              : _regProcess(regProcess), _sendProcess(sendProcess),
                _regLoad(regLoad), _sendLoad(sendLoad)
{
    if (_regProcess != "")    Mediator::Register(_regProcess, [this](MediatorArg arg){ Process(arg); });
    if (_regProcess != "")   Mediator::Register(_regLoad, [this](MediatorArg arg){ Load(arg); });
}

void UserLoginProcessor::Process(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    User* user = nullptr;
    if (success)
    {
        if (user)
        {
            success = ValidateUser(*user, errorMessage);
        }
    }
    Mediator::Call(_sendProcess, nullptr, success, errorMessage);
}

void UserLoginProcessor::Load(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    User* user = nullptr;
    if (success)
    {
        if (user)
        {
            success = ValidateUser(*user, errorMessage);
        }
    }
    Mediator::Call(_sendLoad, nullptr, success, errorMessage);
}

bool UserLoginProcessor::ValidateUser(const User& user, std::string& errorMessage) const
{
    bool success = true;
    auto userName = user.GetName();
    auto password = user.GetPassword();
    success &= ValidateUserName(userName, errorMessage);
    success &= ValidatePassword(password, errorMessage);
    return success;
}
bool UserLoginProcessor::ValidateUserName(std::string userName, std::string& errorMessage) const
{
    bool success = true;
    std::string pattern = "[a-zA-Z0-9\.]*";
    success &= std::regex_match(userName, std::regex(pattern));
    if (!success)
    {
        errorMessage = "Invalid user name.";
    }
    return success;
}
bool UserLoginProcessor::ValidatePassword(std::string password, std::string& errorMessage) const
{
    bool success = true;
    std::string pattern = "[a-zA-Z0-9\. ]*";
    success &= std::regex_match(userName, std::regex(pattern));
    if (!success)
    {
        errorMessage = "Invalid password.";
    }
    return success;
}
