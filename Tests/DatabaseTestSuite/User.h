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

    string GetType(void);

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

string User::GetType(void)
{
    return to_string(m_type);
}

string User::Parse()
{
    return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetPass() + "\', \'" + this->GetType() + " );");
}

#endif
