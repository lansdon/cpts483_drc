#include "User.h"

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

void User::SetName(string name)
{
    m_userName = name;
}

void User::SetPassword(string password)
{
    m_password = password;
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
