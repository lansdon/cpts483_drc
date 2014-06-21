#include "Basket.h"

#define table_name "Basket"

Basket::Basket()
{
}

Basket::Basket(QString name)
{
    m_name = name;
}

Basket::Basket(QString* name)
{
    m_name = *name;
}

void Basket::SetName(QString name)
{
    m_name = name;
}

QString Basket::GetName(void)
{
    return m_name;
}

//For the sake of readbility.  A lot of code though.
QString Basket::Parse()
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += single_quote + this->GetName() + single_quote;

    return toReturn;

    //return QString("VALUES (\'" + this->GetName() + "\', \'" + this->GetTime() + " );");
}

QString Basket::table(void)
{
    return QString(table_name);
}

QString Basket::DuplicateQuery(void)
{
    static QString single_quote("\'");

    QString toReturn;

    toReturn += "SELECT * FROM ";
    toReturn += table_name;
    toReturn += " WHERE Basket_name like ";
    toReturn += single_quote + this->GetName() + single_quote;

    return toReturn;

    //return QString("Select * from table_name where name like \'" + this->GetName() + "\' and where time = " + this->GetTime()
}

QString Basket::SearchQuery(void)
{
    static QString single_quote("\'");

    QString toReturn;
    bool firstFilter = true;
    toReturn += "SELECT * FROM ";
    toReturn += table_name;
    if(this->GetName() != "")
    {
        toReturn += " WHERE Basket_name like ";
        toReturn += single_quote + this->GetName() + single_quote;
        firstFilter = false;
    }
    return toReturn;

    //return QString("Select * from table_name where name like \'" + this->GetName() + "\' and where time = " + this->GetTime()
}
