#ifndef FRUIT_H
#define FRUIT_H

#include "DBBaseObject.h"

#include <ctime>
#include <string>

using namespace std;

class Fruit : public DBBaseObject
{
    string m_name;

    time_t m_timestamp;

public:


    Fruit();

    Fruit(string name);

    Fruit(string *name);

    void SetName(string name);

    string GetName(void);

    string GetTime(void);

    string BreakApart(void);

    string Parse(void);
};

#endif
