#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"

#include <string>
#include "UserType.h"

using namespace std;

class User : public DBBaseObject
{
private:
    string m_userName;
    string m_password;
    UserType m_type;

public:
    User(string name, string pass);

    string GetName(void);

    string GetPass(void);

    UserType GetType(void);
    string GetTypeString(void);

    string Parse(void);
};

User::User(string name, string pass)
{
    m_userName = name;
    m_password = pass;
    m_type = ADMIN;
}

string User::GetName(void)
{
    return m_userName;
}

string User::GetPass(void)
{
    return m_password;
}

string User::GetTypeString(void)
{
    switch(m_type)
    {
        case SUPER_USER: return "Super User"; break;
        case ADMIN: return "Admin"; break;
        case NORMAL_USER: return "User"; break;
        default: return "Invalid"; break;
    }
}

UserType User::GetType(void)
{
    return m_type;
}

string User::Parse()
{
    return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetPass() + "\', \'" + this->GetTypeString() + " );");
}

#endif
