#include "Person.h"

Person::Person()
{
    _firstName = "";
}

Person::Person(QString n)
{
    _firstName = n.toUtf8().constData();
}
