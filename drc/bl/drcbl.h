#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "mediationprocess.h"
#include "Mediator.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();
    void AuthenticateUser(MediatorArg arg) const;
    void ValidateMediationProcess(MediatorArg arg) const;
    void LoadMediationProcess(MediatorArg arg) const;
    void LoadRecentMediations(MediatorArg arg) const;
    void SendResults(MediatorArg arg);

private:
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
