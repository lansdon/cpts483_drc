#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>

class Person
{
private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;

    std::string _street;
    std::string _unit;
    std::string _city;
    std::string _state;
    std::string _zip;
    std::string _county;

    std::string _primaryPhone;
    std::string _primaryPhoneExt;
    std::string _secondaryPhone;
    std::string _secondaryPhoneExt;

    std::string _email;

    unsigned int _numberInHousehold;

    std::string _attorney;

    bool _isAttorney;
    std::string _assistantName;
    std::string _assistantEmail;
    std::string _assistantNumber;
    std::string _assistantNumberExt;

public:
    Person();
    Person(QString n);

    // Accessors
     void setName(std::string fName, std::string mName, std::string lName) { _firstName=fName; _middleName=mName; _lastName=lName;}
    std::string getFirstName() const { return _firstName; }
    std::string getMiddleName() const { return _middleName; }
    std::string getLastName() const { return _lastName; }
    void setFirstName(std::string fName) { _firstName = fName; }
    void setMiddleName(std::string mName) { _middleName = mName; }
    void setLastName(std::string lName) { _lastName = lName; }

    std::string getStreet() const { return _street; }
    void setStreet(std::string value) { _street = value; }
    std::string getUnit() const { return _unit; }
    void setUnit(std::string value) { _unit = value; }
    std::string getCity() const { return _city; }
    void setCity(std::string value) { _city = value; }
    std::string getState() const { return _state; }
    void setState(std::string value) { _state = value; }
    std::string getZip() const { return _zip; }
    void setZip(std::string value) { _zip = value; }
    std::string getCounty() const { return _county; }
    void setCounty(std::string value) { _county = value; }

    std::string getPrimaryPhone() const { return _primaryPhone; }
    void setPrimaryPhone(std::string value) { _primaryPhone = value; }
    std::string getPrimaryPhoneExt() const { return _primaryPhoneExt; }
    void setPrimaryPhoneExt(std::string value) { _primaryPhoneExt = value; }

    std::string getSecondaryPhone() const { return _secondaryPhone; }
    void setSecondaryPhone(std::string value) { _secondaryPhone = value; }
    std::string getSecondaryPhoneExt() const { return _secondaryPhoneExt; }
    void setSecondaryPhoneExt(std::string value) { _secondaryPhoneExt = value; }

    std::string getAssistantPhone() const { return _assistantNumber; }
    void setAssistantPhone(std::string value) { _assistantNumber = value; }
    std::string getAssistantPhoneExt() const { return _assistantNumberExt; }
    void setAssistantPhoneExt(std::string value) { _assistantNumberExt = value; }

    std::string getEmail() const { return _email; }
    void setEmail(std::string value) { _email = value; }

    unsigned int getNumberInHousehold() const { return _numberInHousehold; }
    void setNumberInHousehold(unsigned int value) { _numberInHousehold = value; }

    std::string getAttorney() const { return _attorney; }
    void setAttorney(std::string value) { _attorney = value; }

    // Helpers
    QString FullName() { return QString::fromStdString(_firstName + " " + _lastName); }

    // Test Data - Fill the object with test values in every field.
    static Person *SampleData();
};

#endif // PERSON_H
