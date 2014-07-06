#include "User.h"

User::User()
{
    // filler!  Because this REALLY doesn't need to do anything.
}

User::User(QString name, QString pass, UserTypes type)
{
    m_userName = name;
    m_password = sha256(pass, "");
    m_type = type;
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

void User::SetType(UserTypes Type)
{
    m_type = Type;
}

void User::SetPassword(QString password)
{
    m_password = sha256(password, "");
}

QString User::GetTypeString(void)
{
    switch(m_type)
    {
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
    return QString("'%1', '%2', '%3'")
            .arg(this->GetName())
            .arg(this->GetPass())
            .arg(QString::number(this->GetType()));
}

QString User::GetIdRowName()
{
    return "";
}

QString User::UpdateParse()
{
#warning    TODO - UpdateParse() UNIMPLEMENTED!!
    return "";
}

QString User::table(void)
{
    return QString("User_Table");
}

QString User::DuplicateQuery(void)
{
    return QString("This method in User.cpp has yet to be implemented.");
}

QString User::SearchQuery(void)
{
    return QString("This method in User.cpp has yet to be implemented.");
}
