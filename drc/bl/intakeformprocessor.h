#ifndef INTAKEFORMPROCESSOR_H
#define INTAKEFORMPROCESSOR_H

#include <string>
#include "../drc_shared/models/Intake.h"
#include "../drc_shared/models/Person.h"
#include "Processor.h"

class IntakeFormProcessor: public Processor
{
public:
    IntakeFormProcessor(std::string regProcess="", std::string sendProcess="",
                                             std::string regLoad="", std::string sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    bool ValidateIntakeForm(const Intake& intake, std::string& errorMessage) const;
    bool ValidatePerson(const Person& person, std::string& errorMessage) const;
    bool ValidateTime(time_t time, std::string& errorMessage) const;

    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // INTAKEFORMPROCESSOR_H
