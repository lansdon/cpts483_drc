#include "personvalidator.h"

PersonValidator::PersonValidator()
{
}

bool PersonValidator::Validate(Person* person, QString &errorMessage) const
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

bool PersonValidator::ValidateName(QString name, QString& errorMessage) const
{
    QString test = errorMessage;
    return true;
}
bool PersonValidator::ValidateEmail(QString email, QString &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidatePhoneNumber(QString number, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateExtension(QString extension, QString &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCity(QString city, QString &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCounty(QString county, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateState(QString state, QString &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateZip(QString zip, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateStreet(QString zip, QString &errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateUnit(QString unit, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateNumberInHousehold(int num, QString &errorMessage) const
{
    return true;
}
