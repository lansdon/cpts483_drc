#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"


#include <qstring.h>
#include <qdebug.h>
#include "drc_shared/models/Intake.h"

#include <set>
#include <algorithm>


//namespace drc {
//namespace bl {


DRCBL::DRCBL()
{
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
    // Testing unregister... remove this later.
//    Mediator::Unregister(MKEY_GUI_SUBMIT_FRUIT_NAME, ProcessFruitNameId);
//    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

}
void DRCBL::SendResults(MediatorArg arg)
{
//    Intake intake;
//    MediatorArg arg(&intake);
//    Intake* intakeResult = arg.getArg<Intake*>();

    Intake temp;
    temp.addClaimant("apple");
    temp.addRespondents("peach");
    temp.addRespondents("banana");
    temp.addRespondents("grape");
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

    std::string* fruitName = nullptr;
    if (success)
    {
        fruitName = arg.getArg<std::string*>();

        success = _fruitNameProcessor.ValidateFruitName(fruitName, errorMessage);

    }
    else
    {
        success = false;
        errorMessage = "Incoming arg flagged invalid.";
    }

    qDebug() << "BL -> Validation Complete";
    Mediator::Call(MKEY_BL_VALIDATE_FRUITNAME_DONE, fruitName, success, errorMessage);
}

// end namespaces
//}
//}