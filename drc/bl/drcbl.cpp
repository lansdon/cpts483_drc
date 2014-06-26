#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"
#include "mediationprocess.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include "MediatorKeys.h"

#include <qstring.h>
#include <qdebug.h>
#include "Intake.h"
#include "Fruit.h"
#include <set>
#include <algorithm>


DRCBL::DRCBL()
{

	// Test function - returns sample date to fruit page.
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
}

//  TEST FUNCTION - Returns sample data to the fruitname test page.
void DRCBL::SendResults(MediatorArg arg)
{
/*    MedationProcess temp;
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
*/}

// end namespaces
//}
//}
