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
    Mediator::Register(MKEY_GUI_SEND_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });
}

void DRCBL::ProcessFruitName(MediatorArg arg)
{
    bool success = true;
    std::string errorMessage;

    if (arg.IsSuccessful())
    {
        auto fruitName = arg.getArg<std::string*>();
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

    qDebug() << "BL -> Send result back";
    Mediator::Call(MKEY_BL_SEND_FRUIT_NAME_RESULT, nullptr, success, errorMessage);
}

// end namespaces
//}
//}
