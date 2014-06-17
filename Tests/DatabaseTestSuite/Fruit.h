#ifndef FRUIT_H
#define FRUIT_H

#include "DBBaseObject.h"

#include <ctime>
#include <string>

using namespace std;

class Fruit : public DBBaseObject
{
private:
    QString m_name;

    time_t m_timestamp;

public:


    Fruit();

    Fruit(QString name);

    Fruit(QString *name);

    void SetName(QString name);

    void SetTime(int time);

    QString GetName(void);
    
    QString GetTime(void);
    
    QString BreakApart(void);
    
    QString Parse(void);
    
    QString table(void);

    QString DuplicateQuery(void);

    QString SearchQuery(void);
    
};

#endif
