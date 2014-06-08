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

    std::string _home;
    std::string _homeExt;
    std::string _work;
    std::string _workExt;
    std::string _mobile;
    std::string _mobileExt;

    std::string _email;

    unsigned int _numberInHousehold;

    std::string _attorney;

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

    std::string getHomePhone() const { return _home; }
    void setHomePhone(std::string value) { _home = value; }
    std::string getHomePhoneExt() const { return _homeExt; }
    void setHomePhoneExt(std::string value) { _homeExt = value; }

    std::string getWorkPhone() const { return _work; }
    void setWorkPhone(std::string value) { _work = value; }
    std::string getWorkPhoneExt() const { return _workExt; }
    void setWorkPhoneExt(std::string value) { _workExt = value; }

    std::string getMobilePhone() const { return _mobile; }
    void setMobilePhone(std::string value) { _mobile = value; }
    std::string getMobilePhoneExt() const { return _mobileExt; }
    void setMobilePhoneExt(std::string value) { _mobileExt = value; }

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
