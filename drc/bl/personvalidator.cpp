#include "personvalidator.h"

PersonValidator::PersonValidator()
{
}

bool PersonValidator::Validate(Person* person, QString& errorMessage) const
{
    bool success = true;

    success &= ValidateName(person->getFirstName(), errorMessage);
    success &= ValidateName(person->getMiddleName(), errorMessage);
    success &= ValidateName(person->getLastName(), errorMessage);
    success &= ValidateStreet(person->getStreet(), errorMessage);
    success &= ValidateUnit(person->getUnit(), errorMessage);

    return success;
}

bool PersonValidator::ValidateName(std::string name, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateEmail(std::string email, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidatePhoneNumber(std::string number, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCity(std::string city, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateZip(std::string zip, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateStreet(std::string zip, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateUnit(std::string unit, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateNumberInHousehold(int num, QString& errorMessage) const
{
    return true;
}
