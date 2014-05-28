#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "drc_shared/mediator/Mediator.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();

    void ProcessFruitName(MediatorArg arg);

    // Mediator Callbacks.
    MediatorId ProcessFruitNameId;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
