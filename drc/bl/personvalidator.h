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
    bool ValidateName(QString name, QString& errorMessage) const;
    bool ValidateEmail(QString email, QString& errorMessage) const;
    bool ValidatePhoneNumber(QString number, QString &errorMessage) const;
    bool ValidateExtension(QString extension, QString& errorMessage) const;
    bool ValidateCity(QString city, QString& errorMessage) const;
    bool ValidateCounty(QString county, QString &errorMessage) const;
    bool ValidateState(QString state, QString& errorMessage) const;
    bool ValidateZip(QString zip, QString &errorMessage) const;
    bool ValidateStreet(QString zip, QString& errorMessage) const;
    bool ValidateUnit(QString unit, QString &errorMessage) const;
    bool ValidateNumberInHousehold(int num, QString& errorMessage) const;
};

#endif // PERSONVALIDATOR_H
