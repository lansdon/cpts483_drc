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
    void SetName(string name);
    void SetPassword(string password);
    string Parse(void);
};




#endif
