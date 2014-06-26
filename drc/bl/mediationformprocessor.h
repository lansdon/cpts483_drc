#ifndef MEDIATIONFORMPROCESSOR_H
#define MEDIATIONFORMPROCESSOR_H

#include <string>
#include "Intake.h"
#include "Person.h"
#include "Processor.h"

class MediationFormProcessor: public Processor
{
public:
<<<<<<< HEAD:drc/bl/mediationformprocessor.h
    MediationFormProcessor(std::string regProcess="", std::string sendProcess="",
                                             std::string regLoad="", std::string sendLoad="");
=======
    IntakeFormProcessor(QString regProcess="", QString sendProcess="",
                                             QString regLoad="", QString sendLoad="");
>>>>>>> origin/master:drc/bl/intakeformprocessor.h
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
<<<<<<< HEAD:drc/bl/mediationformprocessor.h
    bool ValidateMediationForm(MedationProcess* mediationProcess, std::string& errorMessage) const;
    bool ValidateTime(time_t time, std::string& errorMessage) const;
=======
    bool ValidateIntakeForm(const Intake& intake, QString& errorMessage) const;
    bool ValidatePerson(const Person& person, QString& errorMessage) const;
    bool ValidateTime(time_t time, QString& errorMessage) const;
>>>>>>> origin/master:drc/bl/intakeformprocessor.h

    QString _regProcess;
    QString _sendProcess;
    QString _regLoad;
    QString _sendLoad;
};

#endif // MEDIATIONFORMPROCESSOR_H
