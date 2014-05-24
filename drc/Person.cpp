#include "Person.h"

Person::Person(QString n)
{
    _name = n.toUtf8().constData();
}
