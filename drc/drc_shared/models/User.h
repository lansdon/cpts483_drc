#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"

#include <string>
#include "drctypes.h"

class User : public DBBaseObject
{
private:
    QString m_userName;
    QString m_password;
    UserTypes m_type;

public:
	User();
    User(QString name, QString pass);

    QString GetName(void);
    void SetName(QString name);
    QString GetPass(void);
    void SetPassword(QString password);

    UserTypes GetType(void);
    QString GetTypeString(void);

    QString Parse(void);
};

#endif
