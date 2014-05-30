#include "intakeformprocessor.h"

#include <regex>

IntakeFormProcessor::IntakeFormProcessor()
{
}

bool IntakeFormProcessor::ValidateIntakeForm(Intake* intakeForm, std::string& errorMessage) const
{
    bool success = true;
    if (intakeForm)
    {
        for (int i = 0; i < intakeForm->getNumberOfPeople(); i++)
        {
            success = ValidatePerson(intakeForm->getPerson(i), errorMessage);
            if (!success) break;
        }
        success = ValidateTime(intakeForm->getTime(), errorMessage);
    }
    else
    {
        success = false;
        errorMessage = "No intake form.";
    }
    return success;
}

bool IntakeFormProcessor::ValidatePerson(Person person, std::string& errorMessage) const
{
    return false;
}

bool IntakeFormProcessor::ValidateTime(time_t time, std::string& errorMessage) const
{
    return false;
}
