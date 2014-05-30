#ifndef INTAKEFORMPROCESSOR_H
#define INTAKEFORMPROCESSOR_H

#include <string>

#include "../drc_shared/models/Intake.h"
#include "../drc_shared/models/Person.h"

class IntakeFormProcessor
{
public:
    IntakeFormProcessor();
    bool ValidateIntakeForm(Intake* intakeForm, std::string& errorMessage) const;

private:
    bool ValidatePerson(Person person, std::string& errorMessage) const;
    bool ValidateTime(time_t time, std::string& errorMessage) const;
};

#endif // INTAKEFORMPROCESSOR_H
