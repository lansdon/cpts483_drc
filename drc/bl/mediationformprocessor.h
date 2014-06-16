#ifndef MEDIATIONFORMPROCESSOR_H
#define MEDIATIONFORMPROCESSOR_H

#include <string>
#include "Intake.h"
#include "Person.h"
#include "Processor.h"

class MediationFormProcessor: public Processor
{
public:
    MediationFormProcessor(std::string regProcess="", std::string sendProcess="",
                                             std::string regLoad="", std::string sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    bool ValidateMediationForm(MedationProcess* mediationProcess, std::string& errorMessage) const;
    bool ValidateTime(time_t time, std::string& errorMessage) const;

    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // MEDIATIONFORMPROCESSOR_H
