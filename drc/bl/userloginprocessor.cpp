#include "userloginprocessor.h"
#include "../drc_shared/mediator/Mediator.h"
#include "Crypto/SHA256_Crypto.h"

#include <qstring.h>
#include <qdebug.h>

UserLoginProcessor::UserLoginProcessor(std::string authUser, std::string sendUser,
                                       std::string requestSalt, std::string receiveSalt)
              : _sendUser(sendUser), _requestSalt(requestSalt)
{
    Mediator::Register(authUser, [this](MediatorArg arg){ Authenticate(arg); });
    Mediator::Register(receiveSalt, [this](MediatorArg arg){ ReceiveSalt(arg); });
    _user = nullptr;
    _userName = nullptr;
}

// Authentication
void UserLoginProcessor::Authenticate(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();
    User* user = nullptr;
    if (success)
    {
        user = arg.getArg<User*>();
        if (user)
        {
            _user = user;
            CleanUserName();
            _userName = new std::string(user->GetName().toStdString());
        }
        else
        {
            errorMessage = "Empty user argument.";
            success = false;
        }
    }
    if (!success) Mediator::Call(_sendUser, nullptr, success, errorMessage);
    else Mediator::Call(_requestSalt, _userName, success, errorMessage);
}

void UserLoginProcessor::ReceiveSalt(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();
    std::string* salt = nullptr;
    if (success)
    {
        salt = arg.getArg<std::string*>();
        if (salt)
        {
            if (_user)
            {
                auto encryptedPw = sha256(_user->GetPass().toStdString(), *salt);
                _user->SetPassword(QString::fromStdString(encryptedPw));
            }
            else
            {
                errorMessage = "Empty user.";
                success = false;
            }
        }
        else
        {
            errorMessage = "Empty user argument.";
            success = false;
        }
    }
    Mediator::Call(_sendUser, _user, success, errorMessage);
}

void UserLoginProcessor::CleanUserName()
{
    if (_userName != nullptr) delete _userName;
    _userName = nullptr;
}

UserLoginProcessor::~UserLoginProcessor()
{
    CleanUserName();
}


// Process new User
void UserLoginProcessor::Process(MediatorArg arg) {}
void UserLoginProcessor::Load(MediatorArg arg) {}
