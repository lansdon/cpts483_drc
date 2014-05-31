#include "Person.h"

Person::Person()
{
    _name = "";
}

Person::Person(QString n)
{
    _name = n.toUtf8().constData();
}

std::string Person::getName() const
{
    return _name;
}
