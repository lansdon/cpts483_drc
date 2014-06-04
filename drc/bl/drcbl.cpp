#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"

#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"

#include <qstring.h>
#include <qdebug.h>

#include "drc_shared/models/Intake.h"
#include "Fruit.h"

#include <set>
#include <algorithm>


//namespace drc {
//namespace bl {


DRCBL::DRCBL()
{
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
    Mediator::Register(MKEY_GUI_LOAD_INTAKE_FORM, [this](MediatorArg arg){ValidateLoadIntakeRequest(arg); });
    Mediator::Register(MKEY_GUI_SUBMIT_INTAKE_FORM, [this](MediatorArg arg){ValidateSaveIntakeRequest(arg); });

}
void DRCBL::SendResults(MediatorArg arg)
{
//    Intake intake;
//    MediatorArg arg(&intake);
//    Intake* intakeResult = arg.getArg<Intake*>();

    Intake temp;
    Person claimant = Person::SampleData();
    claimant.setFirstName("apple");
    temp.addClaimant(claimant);

    Person p1 = Person::SampleData();
    p1.setFirstName("peach");
    temp.addRespondents(p1);

    Person p2 = Person::SampleData();
    p2.setFirstName("banana");
    temp.addRespondents(p2);

    Person p3 = Person::SampleData();
    p3.setFirstName("grape");
    temp.addRespondents(p3);

    //MediatorArg args(&temp);
    //Intake* intakeResult = args.getArg<Intake*>();
   // qDebug() << QString::fromStdString(intakeResult->getClaimant().getName());
   // qDebug() << QString::fromStdString(intakeResult->getRespondents()[0].getName());

    Mediator::Call(MKEY_BL_RETURN_SEARCH_RESULTS,new Intake(temp));
}

void DRCBL::ProcessFruitName(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Fruit* fruit= nullptr;
    if (success)
    {
        fruit = arg.getArg<Fruit*>();

        success = _fruitNameProcessor.ValidateFruitName(fruit, errorMessage);
    }

    qDebug() << "BL -> Validation Complete";
    Mediator::Call(MKEY_BL_VALIDATE_FRUITNAME_DONE, fruit, success, errorMessage);
}


void DRCBL::ValidateSaveIntakeRequest(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;
    if (success)
    {
        intake = arg.getArg<Intake*>();
        // INSERT CODE HERE
    }

    qDebug() << "BL -> ValidateSaveIntakeRequest Complete";
    Mediator::Call(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, intake, success, errorMessage);
}

void DRCBL::ValidateLoadIntakeRequest(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;
    if (success)
    {
        intake = arg.getArg<Intake*>();
        // INSERT CODE HERE
    }

    qDebug() << "BL -> ValidateLoadIntakeRequest Complete";
    Mediator::Call(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, intake, success, errorMessage);
}
// end namespaces
//}
//}
