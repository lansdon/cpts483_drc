#ifndef PERSONVALIDATOR_H
#define PERSONVALIDATOR_H

#include <QString>

class PersonValidator
{
public:
    PersonValidator();
    Validate(Person* person) const;
private:
    bool validateName(QString name, QString& errorMessage) const;
    bool validateEmail(QString email, QString& errorMessage) const;
    bool ValidatePhoneNumber(QString number, QString& errorMessage) const;
    bool ValidateCity(QString city, QString& errorMessage) const;
    bool ValidateZip(QString zip, QString& errorMessage) const;
    bool ValidateStreet(QString zip, QString& errorMessage) const;
    bool ValidateUnit(QString unit, QString& errorMessage) const;
    bool ValidateNumberInHousehold(int num, QString& errorMessage) const;
};

#endif // PERSONVALIDATOR_H
