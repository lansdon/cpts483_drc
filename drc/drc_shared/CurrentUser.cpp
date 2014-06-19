#include "CurrentUser.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "drctypes.h"

CurrentUser::CurrentUser()
{
    Mediator::Register(MKEY_CURRENT_USER_CHANGED, [this](MediatorArg arg){LoginUser(arg);});
    _currentUser = nullptr;
}

CurrentUser::CurrentUser(const CurrentUser& User)
{
	// Filler
}

CurrentUser& CurrentUser::Instance()
{
    static CurrentUser instance;
	return instance;
}


bool CurrentUser::LoginUser(User* NewUser)
{
    // Maybe do some error checking here.  Maybe make sure the permissions are set right?  IDK...
    Instance()._currentUser = NewUser;

	return true;
}

bool CurrentUser::LoginUser(MediatorArg arg)
{
    Instance()._currentUser = arg.getArg<User*>();
    return arg.IsSuccessful();
}

bool CurrentUser::LogoutUser()
{
	// More error checking possibly?
	// Will have to do more than just set the pointer to null.
    // Some kind of mediator call?
    Instance()._currentUser = nullptr;
	return true;
}

bool CurrentUser::IsLoggedIn()
{
    return (Instance()._currentUser == nullptr);
}
