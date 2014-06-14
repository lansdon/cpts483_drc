#include "User.h"

User::User(QString name, QString pass)
{
    m_userName = name;
    m_password = pass;
    m_type = USER_T_ADMIN;
}

QString User::GetName(void)
{
    return m_userName;
}

QString User::GetPass(void)
{
    return m_password;
}

void User::SetName(QString name)
{
    m_userName = name;
}

void User::SetPassword(QString password)
{
    m_password = password;
}

QString User::GetTypeString(void)
{
    switch(m_type)
    {
        case USER_T_SUPER_USER: return "Super User"; break;
        case USER_T_ADMIN: return "Admin"; break;
        case USER_T_NORMAL: return "User"; break;
        default: return "Invalid"; break;
    }
}

UserTypes User::GetType(void)
{
    return m_type;
}

QString User::Parse()
{
    return QString("VALUES (\'" + this->GetName() + "\', \'" + this->GetPass() + "\', \'" + this->GetTypeString() + " );");
}
