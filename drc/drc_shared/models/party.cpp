#include "party.h"
#include "Person.h"
#include "persondetailsform.h"
#include "drctypes.h"
#include <sstream>

Party::Party()
{
}


// Test Data - Fill the object with test values in every field.
Party *Party::SampleData()
{
    Party *result = new Party();

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();

    result->SetPrimary(*Person::SampleData());
    result->SetAttorney(*Person::SampleData());
    result->AddObserver(Person::SampleData());
    result->AddObserver(Person::SampleData());
    result->AddObserver(Person::SampleData());
    result->AddChild(Person::SampleData());
    result->AddChild(Person::SampleData());

    return result;
}
