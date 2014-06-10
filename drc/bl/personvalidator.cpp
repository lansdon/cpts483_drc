#include "personvalidator.h"

PersonValidator::PersonValidator()
{
}

bool PersonValidator::Validate(Person* person) const
{
    bool success = true;
    QString errorMessage = "";

    success &= validateName(person->getFirstName(), errorMessage);
    success &= validateName(person->getMiddleName(), errorMessage);
    success &= validateName(person->getLastName(), errorMessage);
    success &= validateStreet(person->getStreet(), errorMessage);
    success &= validateUnit(person->getUnit(), errorMessage);
    success &= validate
}

bool PersonValidator::validateName(QString name, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::validateEmail(QString email, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidatePhoneNumber(QString number, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateCity(QString city, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateZip(QString zip, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateStreet(QString zip, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateUnit(QString unit, QString& errorMessage) const
{
    return true;
}
bool PersonValidator::ValidateNumberInHousehold(int num, QString& errorMessage) const
{
    return true;
}
