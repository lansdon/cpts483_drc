#ifndef PERSONVALIDATOR_H
#define PERSONVALIDATOR_H

#include <QString>
#include "Person.h"

class PersonValidator
{
public:
    PersonValidator();
    bool Validate(Person* person, std::string& errorMessage) const;
private:
    bool ValidateName(std::string name, std::string& errorMessage) const;
    bool ValidateEmail(std::string email, std::string& errorMessage) const;
    bool ValidatePhoneNumber(std::string number, std::string &errorMessage) const;
    bool ValidateExtension(std::string extension, std::string& errorMessage) const;
    bool ValidateCity(std::string city, std::string& errorMessage) const;
    bool ValidateCounty(std::string county, std::string &errorMessage) const;
    bool ValidateState(std::string state, std::string& errorMessage) const;
    bool ValidateZip(std::string zip, std::string &errorMessage) const;
    bool ValidateStreet(std::string zip, std::string& errorMessage) const;
    bool ValidateUnit(std::string unit, std::string &errorMessage) const;
    bool ValidateNumberInHousehold(int num, std::string& errorMessage) const;
};

#endif // PERSONVALIDATOR_H
