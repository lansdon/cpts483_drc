#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "drc_shared/mediator/Mediator.h"

#include "fruitnameprocessor.h"
#include "intakeformprocessor.h"
#include "searchusername.h"
#include "userloginprocessor.h"

class MediatorArg;

class DRCBL
{
public:
    DRCBL();

private:
    FruitNameProcessor  _fruitNameProcessor;
    IntakeFormProcessor _intakeFormProcessor;
    SearchUserName      _searchUserName;
    UserLoginProcessor  _userLoginProcessor;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
