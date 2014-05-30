#ifndef INTAKEFORM_H
#define INTAKEFORM_H

#include "drc_shared/models/Person.h"
#include <string>
#include <vector>
#include <ctime>
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/mediator/MediatorArg.h"

//namespace drc {
//namespace gui {
//class IntakeForm;
//}}

class Intake
{
private:
    std::vector<Person> clients;
    time_t enterTime;


public:
    Intake();
    void addPerson(QString input);
    void setTime(time_t t);
    time_t getTime() const;
    Person getPerson(std::string n);
    Person getPerson(int index) const;
    int getNumberOfPeople() const;
};

#endif // INTAKEFORM_H
