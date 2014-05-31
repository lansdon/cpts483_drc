#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>

class Person
{
private:
    std::string _name;
public:
    Person();
    Person(QString n);
    std::string getName() const;
};

#endif // PERSON_H
