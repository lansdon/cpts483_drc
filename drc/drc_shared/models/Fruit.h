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

#endif
