#ifndef FRUITNAMEPROCESSOR_H
#define FRUITNAMEPROCESSOR_H

#include <set>
#include <string>

class FruitNameProcessor
{
public:
    FruitNameProcessor();
    bool ValidateFruitName(std::string* fruitName, std::string& error) const;

private:
    std::set<std::string> _fruitNames;
};

#endif // FRUITNAMEPROCESSOR_H
