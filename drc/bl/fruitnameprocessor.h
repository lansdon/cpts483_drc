#ifndef FRUITNAMEPROCESSOR_H
#define FRUITNAMEPROCESSOR_H

#include <set>
#include <string>
#include "Processor.h"

class FruitNameProcessor: public Processor
{
public:
    FruitNameProcessor(std::string regProcess="", std::string sendProcess="",
                                           std::string regLoad="", std::string sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    std::set<std::string> _fruitNames;
    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // FRUITNAMEPROCESSOR_H
