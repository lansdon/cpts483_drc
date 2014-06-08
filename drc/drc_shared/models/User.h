#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"

#include <string>
#include "drctypes.h"

using namespace std;

class User : public DBBaseObject
{
private:
	string m_userName;
	string m_password;
    UserTypes m_type;

public:
	User();
	User(string name, string pass);

	string GetName(void);
	void SetName(string name);
	string GetPass(void);
	void SetPassword(string password);

    UserTypes GetType(void);
	string GetTypeString(void);

	string Parse(void);
};

#endif
