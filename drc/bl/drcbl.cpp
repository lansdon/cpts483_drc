#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"
#include "mediationprocess.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include "MediatorKeys.h"

#include <qstring.h>
#include <qdebug.h>
#include "stateupdate.h"
#include <set>
#include <algorithm>


DRCBL::DRCBL()
{
    Mediator::Register(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, [this](MediatorArg arg){ValidateMediationProcess(arg);});
    Mediator::Register(MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){LoadMediationProcess(arg);});

	// Test function - returns sample date to fruit page.
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
}

void DRCBL::ValidateMediationProcess(MediatorArg arg) const
{
    QString errorMessage = arg.ErrorMessage();
    bool success = arg.IsSuccessful();
    MediationProcess* mp = nullptr;
    if (success)
    {
       mp = arg.getArg<MediationProcess*>();
       if (mp)
       {
           StateUpdate stateUpdate;
           success = stateUpdate.StateCheck(mp, errorMessage);
       }
       else
       {
           errorMessage = "Invalid Mediation Process";
           success = false;
       }
    }
    Mediator::Call(MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE, mp, success, errorMessage);
}

void DRCBL::LoadMediationProcess(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_VALIDATE_LOAD_MEDIATION_PROCESS_FORM_DONE, arg);
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
