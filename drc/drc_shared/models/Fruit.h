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

    Fruit(string *name);

    void SetName(string name);

    string GetName(void);

    string GetTime(void);

    string BreakApart(void);

    string Parse(void);
};

Fruit::Fruit()
{
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

Fruit::Fruit(string* name)
{
    m_name = *name;
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

void Fruit::SetName(string name)
{
    m_name = name;
}

string Fruit::GetName(void)
{
    return m_name;
}

string Fruit::GetTime(void)
{
    return to_string(m_timestamp);
}

string Fruit::BreakApart()
{
    string toReturn = "VALUES (\'";
    toReturn = toReturn + "VALUES (\'";
    toReturn = toReturn + GetName();
    toReturn = toReturn + "\', \'";
    toReturn = toReturn + GetTime();
    toReturn = toReturn + " );";
    return toReturn;
    //return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}

string Fruit::Parse(void)
{
    return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}

#endif
