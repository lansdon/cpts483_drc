#include "drcbl.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"
#include <qstring.h>
#include <qdebug.h>

#include <set>
#include <algorithm>

//namespace drc {
//namespace bl {


DRCBL::DRCBL()
{
    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

    // Testing unregister... remove this later.
//    Mediator::Unregister(MKEY_GUI_SUBMIT_FRUIT_NAME, ProcessFruitNameId);
//    ProcessFruitNameId = Mediator::Register(MKEY_GUI_SUBMIT_FRUIT_NAME, [this](MediatorArg arg){ ProcessFruitName(arg); });

}

void DRCBL::ProcessFruitName(MediatorArg arg)
{
    std::set<std::string> fruitNames;
    fruitNames.insert("apple");
    fruitNames.insert("orange");
    fruitNames.insert("grapefruit");
    fruitNames.insert("pineapple");

    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    std::string* fruitName = nullptr;
    if (arg.IsSuccessful())
    {
        fruitName = arg.getArg<std::string*>();
        if (fruitName)
        {
            qDebug() << QString("BL -> Processing Fruit Name -> ") << QString::fromStdString(*fruitName);

            auto fruitLower = *fruitName;
            std::transform(fruitLower.begin(), fruitLower.end(), fruitLower.begin(), tolower);
            if (fruitNames.find(fruitLower) == fruitNames.end())
            {
                success = false;
                errorMessage = "Invalid fruit name.";
            }
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
