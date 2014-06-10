#include "personvalidator.h"

PersonValidator::PersonValidator()
{
}

bool PersonValidator::Validate(Person* person, std::string &errorMessage) const
{
    bool success = true;

    success &= ValidateName(person->getFirstName(), errorMessage);
    success &= ValidateName(person->getMiddleName(), errorMessage);
    success &= ValidateName(person->getLastName(), errorMessage);

    success &= ValidateStreet(person->getStreet(), errorMessage);
    success &= ValidateUnit(person->getUnit(), errorMessage);
    success &= ValidateCity(person->getCity(), errorMessage);
    success &= ValidateState(person->getState(), errorMessage);
    success &= ValidateZip(person->getZip(), errorMessage);
    success &= ValidateCounty(person->getCounty(), errorMessage);

    success &= ValidatePhoneNumber(person->getPrimaryPhone(), errorMessage);
    success &= ValidateExtension(person->getPrimaryPhoneExt(), errorMessage);
    success &= ValidatePhoneNumber(person->getSecondaryPhone(), errorMessage);
    success &= ValidateExtension(person->getSecondaryPhoneExt(), errorMessage);

    success &= ValidateEmail(person->getEmail(), errorMessage);

    success &= ValidateNumberInHousehold(person->getNumberInHousehold(), errorMessage);

    success &= ValidateName(person->getAttorney(), errorMessage);

    success &= ValidatePhoneNumber(person->getAssistantPhone(), errorMessage);
    success &= ValidateExtension(person->getAssistantPhoneExt(), errorMessage);

    return success;
}

bool PersonValidator::ValidateName(std::string name, std::string& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateEmail(std::string email, std::string &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidatePhoneNumber(std::string number, std::string& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateExtension(std::string extension, std::string &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCity(std::string city, std::string &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCounty(std::string county, std::string& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateState(std::string state, std::string &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateZip(std::string zip, std::string& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateStreet(std::string zip, std::string &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateUnit(std::string unit, std::string& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateNumberInHousehold(int num, std::string &errorMessage) const
{
    return true;
}
