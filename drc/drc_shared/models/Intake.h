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


public:
    Intake();
    void addClaimant(QString input);
    void addRespondents(QString input);
    void setTime(time_t t);
    time_t getTime() const;
    Person getClaimant() const;
    std::vector<Person> getRespondents() const;

};

#endif // INTAKEFORM_H
