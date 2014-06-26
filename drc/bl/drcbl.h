#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "mediationprocess.h"
#include "Mediator.h"
#include "fruitnameprocessor.h"
#include "userloginprocessor.h"
#include "personprocessor.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();
    void AuthenticateUser(MediatorArg arg) const;

    void SendResults(MediatorArg arg);

private:
    FruitNameProcessor  _fruitNameProcessor;
//    IntakeFormProcessor _intakeFormProcessor;
    UserLoginProcessor _userLoginProcessor;
    PersonProcessor _personProcessor;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
