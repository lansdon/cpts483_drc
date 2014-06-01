#include <algorithm>
#include <qstring.h>
#include <qdebug.h>

#include "../drc_shared/mediator/Mediator.h"
#include "../drc_shared/models/Fruit.h"

#include "fruitnameprocessor.h"

FruitNameProcessor::FruitNameProcessor(std::string regProcess="", std::string sendProcess="",
                                       std::string regLoad="", std::string sendLoad="")
                    : _regProcess(regProcess), _sendProcess(sendProcess),
                      _regLoad(regLoad), _sendLoad(sendLoad)
{
    if (_regProcess != "")    Mediator::Register(_regProcess, [this](MediatorArg arg){ Process(arg); });
    if (_regProcess != "")   Mediator::Register(_regLoad, [this](MediatorArg arg){ Load(arg); });
    _fruitNames.insert("apple");
    _fruitNames.insert("orange");
    _fruitNames.insert("banana");
    _fruitNames.insert("grapefruit");
    _fruitNames.insert("pineapple");
    _fruitNames.insert("strawberry");
    _fruitNames.insert("lemon");
    _fruitNames.insert("lime");
    _fruitNames.insert("watermelon");
    _fruitNames.insert("pear");
    _fruitNames.insert("kiwi");
}

void FruitNameProcessor::Process(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Fruit* fruit = nullptr;
    if (success)
    {
        fruit = arg.getArg<Fruit*>();

        if (fruit)
        {
            qDebug() << QString("BL -> Processing Fruit Name -> ") << QString::fromStdString(fruit->GetName());

            auto fruitLower = fruit->GetName();
            std::transform(fruitLower.begin(), fruitLower.end(), fruitLower.begin(), ::tolower);
            if (_fruitNames.find(fruitLower) == _fruitNames.end())
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

    qDebug() << "BL -> Validation Complete";
    Mediator::Call(_sendProcess, fruit, success, errorMessage);
}

void FruitNameProcessor::Load(MediatorArg)
{

}
