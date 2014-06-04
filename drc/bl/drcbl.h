#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "drc_shared/mediator/Mediator.h"

#include "fruitnameprocessor.h"
#include "intakeformprocessor.h"
#include "userloginprocessor.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();
    void AuthenticateUser(MediatorArg arg) const;

    void SendResults(MediatorArg arg);

private:
    FruitNameProcessor  _fruitNameProcessor;
    IntakeFormProcessor _intakeFormProcessor;
    UserLoginProcessor _userLoginProcessor;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
