#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>

class Person
{
private:
    std::string _name;
public:
    Person(QString n);
};

#endif // PERSON_H
