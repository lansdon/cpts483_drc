#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>
#include "DBBaseObject.h"
#include "drctypes.h"

class Person : public DBBaseObject
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
    CountyIds _county;

    QString _primaryPhone;
    QString _primaryPhoneExt;
    QString _secondaryPhone;
    QString _secondaryPhoneExt;

    QString _email;

    unsigned int _numberInHousehold;
    unsigned int _numberChildrenInHousehold;

    QString _attorney;
    QString _attorneyPhone;
    QString _attorneyEmail;

    //bool _isAttorney;
    QString _assistantName;
    QString _assistantEmail;
    QString _assistantNumber;
    QString _assistantNumberExt;

public:
    Person();
    Person(QString n);
    virtual ~Person();

    // Base Class Virtual Overrides
    QString Parse(void);
    QString ColumnNames();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    QString GetIdRowName();

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
    CountyIds getCounty() { return _county; }
    void setCounty(CountyIds value) { _county = value; }

    QString getPrimaryPhone() const { return _primaryPhone; }
    void setPrimaryPhone(QString value) { _primaryPhone = value; }
    QString getPrimaryPhoneExt() const { return _primaryPhoneExt; }
    void setPrimaryPhoneExt(QString value) { _primaryPhoneExt = value; }

    QString getSecondaryPhone() const { return _secondaryPhone; }
    void setSecondaryPhone(QString value) { _secondaryPhone = value; }
    QString getSecondaryPhoneExt() const { return _secondaryPhoneExt; }
    void setSecondaryPhoneExt(QString value) { _secondaryPhoneExt = value; }

    QString getEmail() const { return _email; }
    void setEmail(QString value) { _email = value; }

    unsigned int getNumberInHousehold() const { return _numberInHousehold; }
    void setNumberInHousehold(unsigned int value) { _numberInHousehold = value; }
    unsigned int getNumberChildrenInHousehold() const { return _numberChildrenInHousehold; }
    void setNumberChildrenInHousehold(unsigned int value) { _numberChildrenInHousehold = value; }


    QString getAttorney() const { return _attorney; }
    void setAttorney(QString value) { _attorney = value; }
    QString getAttorneyPhone() const { return _attorneyPhone; }
    void setAttorneyPhone(QString value) { _attorneyPhone = value; }
    QString getAttorneyEmail() const { return _attorneyEmail; }
    void SetAttorneyEmail(QString value) { _attorneyEmail = value; }
    QString getAssistantName() const { return _assistantName; }
    void setAssistantName(QString value) {_assistantName = value; }
    QString getAssistantPhone() const { return _assistantNumber; }
    void setAssistantPhone(QString value) { _assistantNumber = value; }
    QString getAssistantPhoneExt() const { return _assistantNumberExt; }
    void setAssistantPhoneExt(QString value) { _assistantNumberExt = value; }
    QString getAssistantEmail() const { return _assistantEmail; }
    void setAssistantEmail(QString value) { _assistantEmail = value; }

    // Helpers
    QString FullName() { return (_firstName + " " + _lastName); }
    bool isName() {return !_firstName.isEmpty();}

    bool operator == (const Person &rhs);
    bool operator != (const Person &rhs);

    // Test Data - Fill the object with test values in every field.
    static Person *SampleData();
};

#endif // PERSON_H
