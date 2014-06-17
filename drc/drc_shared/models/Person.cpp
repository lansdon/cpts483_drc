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

QString Person::Parse(void)
{
#warning TODO - Parse() UNIMPLEMENTED!!!!
    // TO DO - PARSE THIS MOFO!!
}

QString Person::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!

}

QString Person::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!

}

QString Person::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!

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

    result->setFirstName(QString::fromStdString("firstname" + strId));
    result->setMiddleName(QString::fromStdString("middlename" + strId));
    result->setLastName(QString::fromStdString("lastname" + strId));
    result->setStreet(QString::fromStdString("street" + strId));
    result->setUnit(QString::fromStdString("unit" + strId));
    result->setCity(QString::fromStdString("city" + strId));
    result->setZip(QString::fromStdString("zip" + strId));
    result->setCounty(QString::fromStdString("county" + strId));
    result->setState(QString::fromStdString("state" + strId));
    result->setPrimaryPhone(QString::fromStdString("PPhone" + strId));
    result->setPrimaryPhoneExt(QString::fromStdString("PPhoneExt" + strId));
    result->setSecondaryPhone(QString::fromStdString("SPhone" + strId));
    result->setSecondaryPhoneExt(QString::fromStdString("SPhoneExt" + strId));
    result->setAssistantPhone(QString::fromStdString("APhone" + strId));
    result->setAssistantPhoneExt(QString::fromStdString("APhoneExt" + strId));
    result->setEmail(QString::fromStdString("email" + strId));
    result->setNumberInHousehold((unsigned int)_SAMPLE_INDEX);
    result->setAttorney(QString::fromStdString("attorney" + strId));

    return result;
}



QString Person::Parse(void)
{
    return QString("'%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', %17, '%18")
            .arg(this->getFirstName())
            .arg(this->getMiddleName())
            .arg(this->getLastName())
            .arg(this->getStreet())
            .arg(this->getUnit())
            .arg(this->getCity())
            .arg(this->getState())
            .arg(this->getZip())
            .arg(this->getCounty())
            .arg(this->getPrimaryPhone())
            .arg(this->getPrimaryPhoneExt())
            .arg(this->getSecondaryPhone())
            .arg(this->getSecondaryPhoneExt())
            .arg(this->getAssistantPhone())
            .arg(this->getAssistantPhoneExt())
            .arg(this->getEmail())
            .arg(this->getNumberInHousehold())
            .arg(this->getAttorney());
}

QString Person::table(void)
{
    return QString("Person_Table");
}

QString Person::DuplicateQuery(void)
{
    return QString("");
}

QString Person::SearchQuery(void)
{
    return QString("");
}
