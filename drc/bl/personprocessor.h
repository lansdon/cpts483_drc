#ifndef PERSONPROCESSOR_H
#define PERSONPROCESSOR_H

#include "Processor.h"
#include "personvalidator.h"

class PersonProcessor : public Processor
{
public:
    PersonProcessor(QString regProcess="", QString sendProcess="",
                    QString regLoad="", QString sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    QString _regProcess;
    QString _sendProcess;
    QString _regLoad;
    QString _sendLoad;
};

#endif // PERSONPROCESSOR_H
