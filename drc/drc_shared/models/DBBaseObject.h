#ifndef DBBASEOBJECT_H
#define DBBASEOBJECT_H

#include <QString>
#include <QDateTime>

class DBBaseObject
{
protected:
    QDateTime m_created;
    QDateTime m_updated;

public:
    //Outputs field data into a SQLite appropriate string format
    //for insertion into a database.

    //Object is still subject to change pending discussion with DB Team.
    virtual QString Parse(void) = 0;

    QDateTime GetCreated() { return m_created; }
    QDateTime GetUpdated() { return m_updated; }
};


#endif // DBBASEOBJECT_H
