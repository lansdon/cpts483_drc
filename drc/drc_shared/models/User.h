#ifndef USER_H
#define USER_H

#include <string>
#include "UserType.h"

using namespace std;

class User
{
private:
    string m_userName;
    string m_password;
    UserType m_type;

public:
    User(string name, string pass);

    string GetName(void);
    string GetPassword(void);
    void SetName(string name);
    void SetPassword(string password);
};

#endif
