#ifndef INTAKEFORM_H
#define INTAKEFORM_H
#include "Person.h"
#include <string>
#include <vector>
#include <ctime>
class IntakeForm
{
private:
    std::vector<Person> clients;
    time_t enterTime;
public:
    IntakeForm();
    void addPerson(QString input);
    void setTime(time_t t);
    time_t getTime() const;
    Person getPerson(std::string n);
};

#endif // INTAKEFORM_H
