#ifndef INTAKE_H
#define INTAKE_H

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
    Person claimant;
    std::vector<Person> respondents;
    time_t enterTime;
    std::vector<Person *> _parties;

public:
    Intake();
    void addClaimant(Person input);
    void addRespondents(Person input);
    void setTime(time_t t);
    time_t getTime() const;
    Person* newParty(){Person *p = new Person(); _parties.push_back(p); return p; }
    Person* addParty(Person *p){_parties.push_back(p); return p; }
    int getNumberOfPeople() const;

    Person getClaimant() const;
    std::vector<Person* > getParties() const;
    void clearRespondents();
    void clearParties();
    void setParties(Person *p, int index);

};

#endif // INTAKEFORM_H
