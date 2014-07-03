#include "Person.h"
#include <sstream>

Person::Person()
{
    _firstName = "";
    _numberInHousehold = 0;
}

Person::Person(QString n)
{
    _firstName = n.toUtf8().constData();
    _numberInHousehold = 0;
}

Person::~Person()
{

}

bool Person::operator==(const Person &rhs)
{
    bool result = true;
    if(this->getFirstName() == rhs.getFirstName()
            && this->getLastName() == rhs.getLastName()
            && this->getMiddleName() == rhs.getMiddleName())
        result = false;
    return result;
}

bool Person::operator!=(const Person &rhs)
{

    return !(*this==rhs);
}

QString Person::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!

    return "";
}

QString Person::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!

    return "";
}


// Test Data - Fill the object with test values in every field.
Person *Person::SampleData()
{
    Person *result = new Person();

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    QString strId = QString::fromStdString(ss.str());

    result->setFirstName(QString("firstname" + strId));
    result->setMiddleName(QString("middlename" + strId));
    result->setLastName(QString("lastname" + strId));
    result->setStreet(QString("street" + strId));
    result->setUnit(QString("unit" + strId));
    result->setCity(QString("city" + strId));
    result->setZip(QString("zip" + strId));
    result->setCounty(QString("county" + strId));
    result->setState(QString("state" + strId));
    result->setPrimaryPhone(QString("PPhone" + strId));
    result->setPrimaryPhoneExt(QString("PPhoneExt" + strId));
    result->setSecondaryPhone(QString("SPhone" + strId));
    result->setSecondaryPhoneExt(QString("SPhoneExt" + strId));
    result->setAssistantPhone(QString("APhone" + strId));
    result->setAssistantPhoneExt(QString("APhoneExt" + strId));
    result->setEmail(QString("email" + strId));
    result->setNumberInHousehold((unsigned int)_SAMPLE_INDEX);
    result->setAttorney(QString("attorney" + strId));

    return result;
}



QString Person::Parse(void)
{
    //Name
    QString toReturn = QString("'%1', '%2', '%3',")
            .arg(this->getFirstName().replace("'", "''"))
            .arg(this->getMiddleName().replace("'", "''"))
            .arg(this->getLastName().replace("'", "''"));

    //Address
    toReturn += QString(" '%1', '%2', '%3', '%4', '%5', '%6',")
            .arg(this->getStreet().replace("'", "''"))
            .arg(this->getUnit().replace("'", "''"))
            .arg(this->getCity().replace("'", "''"))
            .arg(this->getState().replace("'", "''"))
            .arg(this->getZip().replace("'", "''"))
            .arg(this->getCounty().replace("'", "''"));

    //Phone Number
    toReturn += QString(" '%1', '%2', '%3',")
            .arg(this->getPrimaryPhone().replace("'", "''"))
            .arg(this->getSecondaryPhone().replace("'", "''"))
            .arg(this->getAssistantPhone().replace("'", "''"));

    //Other
    toReturn += QString(" '%1', %2, '%3'")
            .arg(this->getEmail().replace("'", "''"))
            .arg(this->getNumberInHousehold())
            .arg(this->getAttorney().replace("'", "''"));

    return toReturn;
}

QString Person::UpdateParse()
{
    //Name
    QString toUpdate = QString("First_Name = '%1', middle_name = '%2', last_name = '%3',")
            .arg(this->getFirstName().replace("'", "''"))
            .arg(this->getMiddleName().replace("'", "''"))
            .arg(this->getLastName().replace("'", "''"));

    //Address
    toUpdate += QString(" street_name = '%1', unit_name = '%2', city_name = '%3', state_name = '%4', zip_code = '%5', county_name = '%6',")
            .arg(this->getStreet().replace("'", "''"))
            .arg(this->getUnit().replace("'", "''"))
            .arg(this->getCity().replace("'", "''"))
            .arg(this->getState().replace("'", "''"))
            .arg(this->getZip().replace("'", "''"))
            .arg(this->getCounty().replace("'", "''"));

    //Phone Number
    toUpdate += QString(" primary_phone =  '%1', secondary_phone = '%2', assistance_phone = '%3',")
            .arg(this->getPrimaryPhone().replace("'", "''"))
            .arg(this->getSecondaryPhone().replace("'", "''"))
            .arg(this->getAssistantPhone().replace("'", "''"));

    //Other
    toUpdate += QString(" email_address = '%1', number_in_house = %2, attorney_name = '%3'")
            .arg(this->getEmail().replace("'", "''"))
            .arg(this->getNumberInHousehold())
            .arg(this->getAttorney().replace("'", "''"));

    return toUpdate;
}

QString Person::GetIdRowName()
{
    return "person_id";
}

QString Person::table(void)
{
    return QString("Person_Table");
}
