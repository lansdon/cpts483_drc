#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <iostream>
#include <time.h>
#include "User.h"
#include "MediatorArg.h"

/*!
 * \brief The CurrentUser class.
 *        Holds a reference to the currently logged in user.
 *
 * The CurrentUser will be used to identify the level of access
 * to certain features within the program. For example Admin type users
 * get teh admin menu.
 */
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

    static void Init();
};

#endif
