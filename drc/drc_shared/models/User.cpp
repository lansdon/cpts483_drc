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

string User::GetType(void)
{
    return to_string(m_type);
}

string User::Parse()
{
    return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetPass() + "\', \'" + this->GetType() + " );");
}

void User::SetName(string name)
{
    m_userName = name;
}

void User::SetPassword(string password)
{
    m_password = password;
}
