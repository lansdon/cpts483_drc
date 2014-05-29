#ifndef DRCDB_H
#define DRCDB_H
#include "drc_shared/mediator/Mediator.h"

class DRCDB
{
public:
    DRCDB();

private:
    MediatorId _persistFruitNameId;

    void persistFruitName(MediatorArg arg);
};

#endif // DRCDB_H
