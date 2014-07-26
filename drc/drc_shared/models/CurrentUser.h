#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <iostream>
#include <time.h>
#include "User.h"

/*!
 * \brief The UserInfo class
 */
class UserInfo
{
private:
	UserInfo();
	UserInfo(const UserInfo &);

	User	*CurrentUser;
	clock_t	TimeOfLastAction;
	int		TimeOutTheshold;
    /*!
     * \brief ResetTime
     */
	static void ResetTime();
public:
    /*!
     * \brief Instance
     * \return
     */
	static UserInfo& Instance();
    /*!
     * \brief LoginUser
     * \param NewUser
     * \return
     */
	static bool LoginUser(User *NewUser);
    /*!
     * \brief LogoutUser
     * \return
     */
    static bool LogoutUser();
    /*!
     * \brief IsLoggedIn
     * \return
     */
    static bool IsLoggedIn();
    /*!
     * \brief SetTimeoutTheshold
     * \param Time
     */
	static void SetTimeoutTheshold(int Time);
    /*!
     * \brief IsTimedOut
     * \return
     */
	static bool IsTimedOut();

};

#endif
