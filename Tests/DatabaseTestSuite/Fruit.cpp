#include "Fruit.h"

#define table_name "Albertsons"

Fruit::Fruit()
{
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

Fruit::Fruit(QString name)
{
    m_name = name;
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

Fruit::Fruit(QString* name)
{
    m_name = *name;
    time_t createTime;
    time(&createTime);
    m_timestamp = createTime;
}

void Fruit::SetName(QString name)
{
    m_name = name;
}

QString Fruit::GetName(void)
{
    return m_name;
}

QString Fruit::GetTime(void)
{
    return QString::number(m_timestamp);
}

//For the sake of readbility.  A lot of code though.
QString Fruit::Parse()
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += single_quote + this->GetName() + single_quote;

    toReturn += ", ";

    toReturn += this->GetTime();

    return toReturn;

    //return QString("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}

QString Fruit::table(void)
{
    return QString(table_name);
}

QString Fruit::DuplicateQuery(void)
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += "SELECT * FROM ";
    toReturn += table_name;
    toReturn += " WHERE fruit_name like ";
    toReturn += single_quote + this->GetName() + single_quote;
    toReturn += " AND time_stamp = ";
    toReturn += this->GetTime();

    return toReturn;

    //return QString("Select * from table_name where name like \'" + this->GetName() + "\' and where time = " + this->GetTime()
}
