#include <qstring.h>
#include <qdebug.h>
#include <algorithm>

#include "fruitnameprocessor.h"

FruitNameProcessor::FruitNameProcessor()
{
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

bool FruitNameProcessor::ValidateFruitName(std::string* fruitName, std::string& errorMessage) const
{
    bool success = true;
    if (fruitName)
    {
        qDebug() << QString("BL -> Processing Fruit Name -> ") << QString::fromStdString(*fruitName);

        auto fruitLower = *fruitName;
        std::transform(fruitLower.begin(), fruitLower.end(), fruitLower.begin(), tolower);
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
    return success;
}
