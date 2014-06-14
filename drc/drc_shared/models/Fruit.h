#ifndef FRUIT_H
#define FRUIT_H

#include "DBBaseObject.h"

#include <ctime>

class Fruit : public DBBaseObject
{
    QString m_name;

public:

    Fruit();

    Fruit(QString name);

    Fruit(QString *name);

    void SetName(QString name);

    QString GetName(void);

    QString GetTime(void);

    QString BreakApart(void);

    QString Parse(void);
};

#endif
