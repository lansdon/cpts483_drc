#ifndef DBBASEOBJECT_H
#define DBBASEOBJECT_H

#include <QString>

class DBBaseObject
{

public:
    //Outputs field data into a SQLite appropriate string format
    //for insertion into a database.

    //Object is still subject to change pending discussion with DB Team.
    virtual QString Parse(void) = 0;

    virtual QString table() = 0;
};


#endif // DBBASEOBJECT_H
