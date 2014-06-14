#include "Fruit.h"

Fruit::Fruit()
{
    m_created = QDateTime::currentDateTime();
}

Fruit::Fruit(QString name)
{
    m_name = name;
    m_created = QDateTime::currentDateTime();
}

Fruit::Fruit(QString* name)
{
    m_name = *name;
    m_created = QDateTime::currentDateTime();
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
    return m_created.toString("MM/dd/yy");
}

//For the sake of readbility.  A lot of code though.
QString Fruit::Parse()
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += " values";

    toReturn += "(";

    toReturn += this->GetTime();

    toReturn += ", ";

    toReturn += single_quote + this->GetName() + single_quote;

    toReturn += ")";

    return toReturn;

    //return string("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}
