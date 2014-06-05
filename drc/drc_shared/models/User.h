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
    void SetName(string name);
    string GetPass(void);
    void SetPassword(string password);

    UserType GetType(void);
    string GetTypeString(void);

    string Parse(void);
};

#endif
