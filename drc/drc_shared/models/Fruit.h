#ifndef FRUIT_H
#define FRUIT_H

#include <ctime>
#include <string>

using namespace std;

class Fruit
{
    string m_name;
    time_t m_timestamp;

public:
    Fruit();

    Fruit(string name);

    void SetName(string name);

    string GetName(void);
};

Fruit::Fruit()
{
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

Fruit::Fruit(string name)
{
    m_name = name;
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

#endif
