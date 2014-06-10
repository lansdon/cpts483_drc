#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"

#include "Mediator.h"
#include "MediatorArg.h"
#include "MediatorKeys.h"

#include <qstring.h>
#include <qdebug.h>
#include "Intake.h"
#include "Fruit.h"
#include <set>
#include <algorithm>


//namespace drc {
//namespace bl {


DRCBL::DRCBL()
      : _fruitNameProcessor(MKEY_GUI_SUBMIT_FRUIT_NAME, MKEY_BL_VALIDATE_FRUITNAME_DONE, "", ""),
        _intakeFormProcessor(MKEY_GUI_SUBMIT_INTAKE_FORM, MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE,
                             MKEY_GUI_LOAD_INTAKE_FORM, MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE),
        _userLoginProcessor(MKEY_GUI_AUTHENTICATE_USER, MKEY_BL_AUTHENTICATE_USER_DONE, MKEY_BL_REQUEST_SALT, MKEY_DB_SEND_SALT),
        _personProcessor(MKEY_GUI_SUBMIT_PERSON_FORM, MKEY_BL_VALIDATE_SAVE_PERSON_FORM_DONE, MKEY_GUI_LOAD_PERSON_FORM, MKEY_BL_VALIDATE_LOAD_PERSON_FORM_DONE)
{
	// Test function - returns sample date to fruit page.
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
}

//  TEST FUNCTION - Returns sample data to the fruitname test page.
void DRCBL::SendResults(MediatorArg arg)
{
    Intake temp;
    Person *claimant = Person::SampleData();
    claimant->setFirstName("apple");
    temp.addParty(claimant);

    Person *p1 = Person::SampleData();
    p1->setFirstName("peach");
    temp.addParty(p1);

    Person *p2 = Person::SampleData();
    p2->setFirstName("banana");
    temp.addParty(p2);

    Person *p3 = Person::SampleData();
    p3->setFirstName("grape");
    temp.addParty(p3);

    Mediator::Call(MKEY_BL_RETURN_SEARCH_RESULTS,new Intake(temp));
}

// end namespaces
//}
//}
