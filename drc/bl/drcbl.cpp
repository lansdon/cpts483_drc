#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"

//namespace drc {
//namespace bl {


DRCBL::DRCBL()
{
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

    // Testing unregister... remove this later.
//    Mediator::Unregister(MKEY_GUI_SUBMIT_FRUIT_NAME, ProcessFruitNameId);
//    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

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
