#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <iostream>
#include <time.h>

#include "User.h"

class UserInfo
{
private:
	UserInfo();
	UserInfo(const UserInfo &);

	User	*CurrentUser;
	clock_t	TimeOfLastAction;
	int		TimeOutTheshold;

	static void ResetTime();
public:
	static UserInfo& Instance();

	static bool LoginUser(User *NewUser);
	static bool LogoutUser();
	static bool IsLoggedIn();

	static void SetTimeoutTheshold(int Time);

	static bool IsTimedOut();

};

#endif
