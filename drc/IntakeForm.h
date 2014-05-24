#ifndef INTAKEFORM_H
#define INTAKEFORM_H
#include "Person.h"
#include <vector>
#include <ctime>
class IntakeForm
{
private:
    std::vector<Person> clients;
    time_t enterTime;
public:
    IntakeForm();
    void populate(QString input);
    void setTime(time_t t);
};

#endif // INTAKEFORM_H
