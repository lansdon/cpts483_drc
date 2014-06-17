#ifndef FRUITNAMEPROCESSOR_H
#define FRUITNAMEPROCESSOR_H

#include <set>
#include <string>
#include <algorithm>
//#include "Fruit.h"
#include "Processor.h"

class FruitNameProcessor: public Processor
{
public:
    FruitNameProcessor(QString regProcess="", QString sendProcess="",
                                           QString regLoad="", QString sendLoad="");
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);

private:
    std::set<QString> _fruitNames;
    QString _regProcess;
    QString _sendProcess;
    QString _regLoad;
    QString _sendLoad;
};

#endif // FRUITNAMEPROCESSOR_H
