#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"

#include <QString>
#include "drctypes.h"

class User : public DBBaseObject
{
private:
<<<<<<< HEAD
    QString m_userName;
    QString m_password;
=======
	QString m_userName;
	QString m_password;
>>>>>>> b60aac2f58c74fe4f514f9ed72ef50fa449bbf2a
    UserTypes m_type;

public:
	User();
<<<<<<< HEAD
    User(QString name, QString pass);

    QString GetName(void);
    void SetName(QString name);
    QString GetPass(void);
    void SetPassword(QString password);
=======
	User(QString name, QString pass);

    QString GetName(void);
	void SetName(QString name);
    QString GetPass(void);
	void SetPassword(QString password);
>>>>>>> b60aac2f58c74fe4f514f9ed72ef50fa449bbf2a

    UserTypes GetType(void);
    QString GetTypeString(void);

    QString Parse(void);
<<<<<<< HEAD
=======

    QString table(void);

    QString DuplicateQuery(void);

    QString SearchQuery(void);
>>>>>>> b60aac2f58c74fe4f514f9ed72ef50fa449bbf2a
};

#endif
