#ifndef INTAKEFORMPROCESSOR_H
#define INTAKEFORMPROCESSOR_H

#include <string>
#include "Intake.h"
#include "Person.h"
#include "Processor.h"

class IntakeFormProcessor: public Processor
{
public:
    IntakeFormProcessor(QString regProcess="", QString sendProcess="",
                                             QString regLoad="", QString sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    bool ValidateIntakeForm(const Intake& intake, QString& errorMessage) const;
    bool ValidatePerson(const Person& person, QString& errorMessage) const;
    bool ValidateTime(time_t time, QString& errorMessage) const;

    QString _regProcess;
    QString _sendProcess;
    QString _regLoad;
    QString _sendLoad;
};

#endif // INTAKEFORMPROCESSOR_H
