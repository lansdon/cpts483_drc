#include "CurrentUser.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "drctypes.h"



CurrentUser::CurrentUser()
{
    /// Make sure to set our _currentUser to null for future checks.
    _currentUser = nullptr;

    /// Register our LoginUser method to calls
    Mediator::Register(MKEY_CURRENT_USER_CHANGED, [this](MediatorArg arg){LoginUser(arg);});
}
CurrentUser::CurrentUser(const CurrentUser& User)
{
    Q_UNUSED(User);
    /// Filler
}

void CurrentUser::Init()
{
    Instance();
}

CurrentUser& CurrentUser::Instance()
{
    static CurrentUser instance;
	return instance;
}

bool CurrentUser::LoginUser(User* NewUser)
{
    /// Maybe do some error checking here.  Maybe make sure the permissions are set right?  IDK...
    Instance()._currentUser = NewUser;

	return true;
}

bool CurrentUser::LoginUser(MediatorArg arg)
{
    Instance()._currentUser = arg.getArg<User*>();
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
    if (Instance()._currentUser->GetType() == USER_T_ADMIN)
    {
        Mediator::Call(MKEY_GUI_SHOW_ADMIN);
    }
    return arg.IsSuccessful();
}

bool CurrentUser::LogoutUser()
{
	// More error checking possibly?
	// Will have to do more than just set the pointer to null.
    // Some kind of mediator call?
    Instance()._currentUser = nullptr;
    Mediator::Call(MKEY_GUI_DISABLE_MENUS);
    Mediator::Call(MKEY_GUI_HIDE_ADMIN);
	return true;
}

bool CurrentUser::IsLoggedIn()
{
    return (Instance()._currentUser == nullptr);
}
