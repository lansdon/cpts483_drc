#include "CurrentUser.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "drctypes.h"


bool UserInfo::IsTimedOut()
{
	return ((clock() - Instance().TimeOfLastAction) / CLOCKS_PER_SEC > Instance().TimeOutTheshold);
}


void UserInfo::ResetTime()
{
	Instance().TimeOfLastAction = clock();
}

void UserInfo::SetTimeoutTheshold(int Time)
{
	Instance().TimeOutTheshold = Time;
	Instance().ResetTime();
}

UserInfo::UserInfo()
{
//	Instance().ResetTime();
    CurrentUser = nullptr;
}

UserInfo::UserInfo(const UserInfo& User)
{
	// Filler
}

UserInfo& UserInfo::Instance()
{
	static UserInfo instance;
	return instance;
}


bool UserInfo::LoginUser(User* NewUser)
{
    // Maybe do some error checking here.  Maybe make sure the permissions are set right?  IDK...
    Instance().CurrentUser = NewUser;
//	Instance().ResetTime();

    // Signal an event that the current user changed.
    Mediator::Call(MKEY_CURRENT_USER_CHANGED, NewUser);

	return true;
}

bool UserInfo::LogoutUser()
{
	// More error checking possibly?
	// Will have to do more than just set the pointer to null.
	// 
	Instance().CurrentUser = nullptr;
	return true;
}

bool UserInfo::IsLoggedIn()
{
	return (Instance().CurrentUser == nullptr);
}
