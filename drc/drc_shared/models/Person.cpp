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


// Test Data - Fill the object with test values in every field.
Person Person::SampleData()
{
    Person result;

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();

    result.setFirstName("firstname" + strId);
    result.setMiddleName("middlename" + strId);
    result.setLastName("lastname" + strId);
    result.setStreet("street" + strId);
    result.setUnit("unit" + strId);
    result.setCity("city" + strId);
    result.setZip("zip" + strId);
    result.setCounty("county" + strId);
    result.setState("state" + strId);
    result.setHomePhone("homephone" + strId);
    result.setHomePhoneExt("homeext" + strId);
    result.setWorkPhone("workophone" + strId);
    result.setWorkPhoneExt("workext" + strId);
    result.setMobilePhone("mobilephone" + strId);
    result.setMobilePhoneExt("mobileext" + strId);
    result.setEmail("email" + strId);
    result.setNumberInHousehold((unsigned int)_SAMPLE_INDEX);
    result.setAttorney("attorney" + strId);

    return result;
}
