#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "drc_shared/mediator/Mediator.h"
#include "fruitnameprocessor.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();

    void ProcessFruitName(MediatorArg arg) const;

    // Mediator Callbacks.
    MediatorId ProcessFruitNameId;

private:
    FruitNameProcessor _fruitNameProcessor;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
