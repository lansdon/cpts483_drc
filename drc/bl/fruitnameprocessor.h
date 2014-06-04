#ifndef FRUITNAMEPROCESSOR_H
#define FRUITNAMEPROCESSOR_H

#include <set>
#include <string>
//#include "Fruit.h"

class Fruit;

class FruitNameProcessor
{
public:
    FruitNameProcessor();
    bool ValidateFruitName(Fruit* fruit, std::string& error) const;

private:
    std::set<std::string> _fruitNames;
};

#endif // FRUITNAMEPROCESSOR_H
