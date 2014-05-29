#include "drcdb.h"
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorKeys.h"
#include "QDebug"

DRCDB::DRCDB()
{
    _persistFruitNameId = Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){ persistFruitName(arg); });

}


void DRCDB::persistFruitName(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();
    std::string* fruitName = nullptr;

    if (arg.IsSuccessful())
    {
        fruitName = arg.getArg<std::string*>();
        if (fruitName)
        {
            qDebug() << QString("DB -> Persisting Fruit Name -> ") << QString::fromStdString(*fruitName);
            // Do stuff here.
         }
        else
        {
            success = false;
            errorMessage = "No fruit name.";
        }
    }

    qDebug() << "DB -> Persist Completed";
    Mediator::Call(MKEY_DB_PERSIST_FRUIT_NAME_DONE, fruitName, success, errorMessage);
}
