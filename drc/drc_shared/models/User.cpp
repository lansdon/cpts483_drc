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

string User::GetPassword(void)
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
