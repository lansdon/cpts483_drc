#ifndef PERSONVALIDATOR_H
#define PERSONVALIDATOR_H

#include <QString>
#include "Person.h"

class PersonValidator
{
public:
    PersonValidator();
    bool Validate(Person* person, QString& errorMessage) const;
private:
    bool ValidateName(std::string name, QString& errorMessage) const;
    bool ValidateEmail(std::string email, QString& errorMessage) const;
    bool ValidatePhoneNumber(std::string number, QString& errorMessage) const;
    bool ValidateCity(std::string city, QString& errorMessage) const;
    bool ValidateZip(std::string zip, QString& errorMessage) const;
    bool ValidateStreet(std::string zip, QString& errorMessage) const;
    bool ValidateUnit(std::string unit, QString& errorMessage) const;
    bool ValidateNumberInHousehold(int num, QString& errorMessage) const;
};

#endif // PERSONVALIDATOR_H
