#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <iostream>
#include <time.h>

#include "User.h"
#include "MediatorArg.h"

class CurrentUser
{
private:
    CurrentUser();
    CurrentUser(const CurrentUser &);

    User	*_currentUser;
public:
    static CurrentUser& Instance();

	static bool LoginUser(User *NewUser);
    static bool LoginUser(MediatorArg arg);
	static bool LogoutUser();
	static bool IsLoggedIn();
};

#endif
