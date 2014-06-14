#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>

class Person
{
private:
    QString _firstName;
    QString _middleName;
    QString _lastName;

    QString _street;
    QString _unit;
    QString _city;
    QString _state;
    QString _zip;
    QString _county;

    QString _primaryPhone;
    QString _primaryPhoneExt;
    QString _secondaryPhone;
    QString _secondaryPhoneExt;

    QString _email;

    unsigned int _numberInHousehold;

    QString _attorney;

    bool _isAttorney;
    QString _assistantName;
    QString _assistantEmail;
    QString _assistantNumber;
    QString _assistantNumberExt;

public:
    Person();
    Person(QString n);

    // Accessors
     void setName(QString fName, QString mName, QString lName) { _firstName=fName; _middleName=mName; _lastName=lName;}
    QString getFirstName() const { return _firstName; }
    QString getMiddleName() const { return _middleName; }
    QString getLastName() const { return _lastName; }
    void setFirstName(QString fName) { _firstName = fName; }
    void setMiddleName(QString mName) { _middleName = mName; }
    void setLastName(QString lName) { _lastName = lName; }

    QString getStreet() const { return _street; }
    void setStreet(QString value) { _street = value; }
    QString getUnit() const { return _unit; }
    void setUnit(QString value) { _unit = value; }
    QString getCity() const { return _city; }
    void setCity(QString value) { _city = value; }
    QString getState() const { return _state; }
    void setState(QString value) { _state = value; }
    QString getZip() const { return _zip; }
    void setZip(QString value) { _zip = value; }
    QString getCounty() const { return _county; }
    void setCounty(QString value) { _county = value; }

    QString getPrimaryPhone() const { return _primaryPhone; }
    void setPrimaryPhone(QString value) { _primaryPhone = value; }
    QString getPrimaryPhoneExt() const { return _primaryPhoneExt; }
    void setPrimaryPhoneExt(QString value) { _primaryPhoneExt = value; }

    QString getSecondaryPhone() const { return _secondaryPhone; }
    void setSecondaryPhone(QString value) { _secondaryPhone = value; }
    QString getSecondaryPhoneExt() const { return _secondaryPhoneExt; }
    void setSecondaryPhoneExt(QString value) { _secondaryPhoneExt = value; }

    QString getAssistantPhone() const { return _assistantNumber; }
    void setAssistantPhone(QString value) { _assistantNumber = value; }
    QString getAssistantPhoneExt() const { return _assistantNumberExt; }
    void setAssistantPhoneExt(QString value) { _assistantNumberExt = value; }

    QString getEmail() const { return _email; }
    void setEmail(QString value) { _email = value; }

    unsigned int getNumberInHousehold() const { return _numberInHousehold; }
    void setNumberInHousehold(unsigned int value) { _numberInHousehold = value; }

    QString getAttorney() const { return _attorney; }
    void setAttorney(QString value) { _attorney = value; }

    // Helpers
    QString FullName() { return _firstName + " " + _lastName; }

    bool operator == (const Person &rhs);
    bool operator != (const Person &rhs);

    // Test Data - Fill the object with test values in every field.
    static Person *SampleData();
};

#endif // PERSON_H
