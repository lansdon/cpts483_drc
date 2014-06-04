#ifndef FRUITNAMEPROCESSOR_H
#define FRUITNAMEPROCESSOR_H

#include <set>
#include <string>
<<<<<<< HEAD
#include <algorithm>
//#include "Fruit.h"
=======
#include "Processor.h"
>>>>>>> b5134fdae3bfd5ab5737e71a1f8fea3a946211c9

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
