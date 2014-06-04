#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "drc_shared/mediator/MediatorArg.h"

class Processor
{
public:
    virtual void Process(MediatorArg arg)=0;
    virtual void Load(MediatorArg arg)=0;
};

#endif // PROCESSOR_H
