#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <string>
#include "DBBaseObject.h"
#include "drctypes.h"

/*!
 * \brief The Person class
 */
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
    /*!
     * \brief Person
     * \param n
     */
    Person(QString n);
    virtual ~Person();

    // Base Class Virtual Overrides
    /*!
     * \brief Parse
     * \return
     */
    QString Parse(void);
    QString ColumnNames();
    /*!
     * \brief UpdateParse
     * \return
     */
    QString UpdateParse();
    /*!
     * \brief table
     * \return
     */
    QString table();
    /*!
     * \brief DuplicateQuery
     * \return
     */
    QString DuplicateQuery();
    /*!
     * \brief SearchQuery
     * \return
     */
    QString SearchQuery();
    /*!
     * \brief GetIdRowName
     * \return
     */
    QString GetIdRowName();

    // Accessors
    /*!
     * \brief setName
     * \param fName
     * \param mName
     * \param lName
     */
    void setName(QString fName, QString mName, QString lName) { _firstName=fName; _middleName=mName; _lastName=lName;}
    /*!
     * \brief getFirstName
     * \return
     */
    QString getFirstName() const { return _firstName; }
    /*!
     * \brief getMiddleName
     * \return
     */
    QString getMiddleName() const { return _middleName; }
    /*!
     * \brief getLastName
     * \return
     */
    QString getLastName() const { return _lastName; }
    /*!
     * \brief setFirstName
     * \param fName
     */
    void setFirstName(QString fName) { _firstName = fName; }
    /*!
     * \brief setMiddleName
     * \param mName
     */
    void setMiddleName(QString mName) { _middleName = mName; }
    /*!
     * \brief setLastName
     * \param lName
     */
    void setLastName(QString lName) { _lastName = lName; }
    /*!
     * \brief getStreet
     * \return
     */
    QString getStreet() const { return _street; }
    /*!
     * \brief setStreet
     * \param value
     */
    void setStreet(QString value) { _street = value; }
    /*!
     * \brief getUnit
     * \return
     */
    QString getUnit() const { return _unit; }
    /*!
     * \brief setUnit
     * \param value
     */
    void setUnit(QString value) { _unit = value; }
    /*!
     * \brief getCity
     * \return
     */
    QString getCity() const { return _city; }
    /*!
     * \brief setCity
     * \param value
     */
    void setCity(QString value) { _city = value; }
    /*!
     * \brief getState
     * \return
     */
    QString getState() const { return _state; }
    /*!
     * \brief setState
     * \param value
     */
    void setState(QString value) { _state = value; }
    /*!
     * \brief getZip
     * \return
     */
    QString getZip() const { return _zip; }
    /*!
     * \brief setZip
     * \param value
     */
    void setZip(QString value) { _zip = value; }
    /*!
     * \brief getCounty
     * \return
     */
    CountyIds getCounty() { return _county; }
    /*!
     * \brief setCounty
     * \param value
     */
    void setCounty(CountyIds value) { _county = value; }
    /*!
     * \brief getPrimaryPhone
     * \return
     */
    QString getPrimaryPhone() const { return _primaryPhone; }
    /*!
     * \brief setPrimaryPhone
     * \param value
     */
    void setPrimaryPhone(QString value) { _primaryPhone = value; }
    /*!
     * \brief getPrimaryPhoneExt
     * \return
     */
    QString getPrimaryPhoneExt() const { return _primaryPhoneExt; }
    /*!
     * \brief setPrimaryPhoneExt
     * \param value
     */
    void setPrimaryPhoneExt(QString value) { _primaryPhoneExt = value; }
    /*!
     * \brief getSecondaryPhone
     * \return
     */
    QString getSecondaryPhone() const { return _secondaryPhone; }
    /*!
     * \brief setSecondaryPhone
     * \param value
     */
    void setSecondaryPhone(QString value) { _secondaryPhone = value; }
    /*!
     * \brief getSecondaryPhoneExt
     * \return
     */
    QString getSecondaryPhoneExt() const { return _secondaryPhoneExt; }
    /*!
     * \brief setSecondaryPhoneExt
     * \param value
     */
    void setSecondaryPhoneExt(QString value) { _secondaryPhoneExt = value; }

    /*!
     * \brief getAssistantPhone
     * \return
     */
    QString getAssistantPhone() const { return _assistantNumber; }
    /*!
     * \brief setAssistantPhone
     * \param value
     */
    void setAssistantPhone(QString value) { _assistantNumber = value; }
    /*!
     * \brief getAssistantPhoneExt
     * \return
     */
    QString getAssistantPhoneExt() const { return _assistantNumberExt; }
    /*!
     * \brief setAssistantPhoneExt
     * \param value
     */
    void setAssistantPhoneExt(QString value) { _assistantNumberExt = value; }
    /*!
     * \brief getEmail
     * \return
     */
    QString getEmail() const { return _email; }
    /*!
     * \brief setEmail
     * \param value
     */
    void setEmail(QString value) { _email = value; }
    /*!
     * \brief getNumberInHousehold
     * \return
     */
    unsigned int getNumberInHousehold() const { return _numberInHousehold; }
    /*!
     * \brief setNumberInHousehold
     * \param value
     */
    void setNumberInHousehold(unsigned int value) { _numberInHousehold = value; }
    /*!
     * \brief getNumberChildrenInHousehold
     * \return
     */
    unsigned int getNumberChildrenInHousehold() const { return _numberChildrenInHousehold; }
    /*!
     * \brief setNumberChildrenInHousehold
     * \param value
     */
    void setNumberChildrenInHousehold(unsigned int value) { _numberChildrenInHousehold = value; }

    /*!
     * \brief getAttorney
     * \return
     */
    QString getAttorney() const { return _attorney; }
    /*!
     * \brief setAttorney
     * \param value
     */
    void setAttorney(QString value) { _attorney = value; }
    /*!
     * \brief getAssistantName
     * \return
     */
    QString getAssistantName() const { return _assistantName; }
    /*!
     * \brief setAssistantName
     * \param value
     */
    void setAssistantName(QString value) {_assistantName = value; }
    /*!
     * \brief getAttorneyPhone
     * \return
     */
    QString getAttorneyPhone() const { return _attorneyPhone; }
    /*!
     * \brief setAttorneyPhone
     * \param value
     */
    void setAttorneyPhone(QString value) { _attorneyPhone = value; }
    /*!
     * \brief getAttorneyEmail
     * \return
     */
    QString getAttorneyEmail() const { return _attorneyEmail; }
    /*!
     * \brief SetAttorneyEmail
     * \param value
     */
    void SetAttorneyEmail(QString value) { _attorneyEmail = value; }
    /*!
     * \brief getAssistantEmail
     * \return
     */
    QString getAssistantEmail() const { return _assistantEmail; }
    /*!
     * \brief setAssistantEmail
     * \param value
     */
    void setAssistantEmail(QString value) { _assistantEmail = value; }

    // Helpers
    /*!
     * \brief FullName
     * \return
     */
    QString FullName() { return (_firstName + " " + _lastName); }
    /*!
     * \brief isName
     * \return
     */
    bool isName() {return !_firstName.isEmpty();}

    bool operator == (const Person &rhs);
    bool operator != (const Person &rhs);

    // Test Data - Fill the object with test values in every field.
    /*!
     * \brief SampleData
     * \return
     */
    static Person *SampleData();
};

#endif // PERSON_H
