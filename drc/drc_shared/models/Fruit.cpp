#include "Fruit.h"

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

string Fruit::GetTime(void)
{
    return to_string(m_timestamp);
}

string Fruit::Parse()
{
    return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}
