#include "drcbl.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"
#include <qstring.h>
#include <qdebug.h>


//namespace drc {
//namespace bl {


DRCBL::DRCBL()
{
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

    // Testing unregister... remove this later.
    Mediator::Unregister(MKEY_GUI_SUBMIT_FRUIT_NAME, ProcessFruitNameId);
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

}

void DRCBL::ProcessFruitName(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    std::string* fruitName = nullptr;
    if (arg.IsSuccessful())
    {
        fruitName = arg.getArg<std::string*>();
        if (fruitName)
        {
            qDebug() << QString("BL -> Processing Fruit Name -> ") << QString::fromStdString(*fruitName);
            // Do stuff here.
         }
        else
        {
            success = false;
            errorMessage = "No fruit name.";
        }
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
