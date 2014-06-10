#ifndef PERSONPROCESSOR_H
#define PERSONPROCESSOR_H

#include "Processor.h"

class PersonProcessor : public Processor
{
public:
    PersonProcessor(std::string regProcess="", std::string sendProcess="",
                    std::string regLoad="", std::string sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // PERSONPROCESSOR_H
