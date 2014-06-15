#include "party.h"
#include "Person.h"
#include "persondetailsform.h"
#include "drctypes.h"
#include <sstream>
#include <QDebug>

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


void Party::RemoveObserver(Person *person)
{
    for(auto it = _observers.begin(); it != _observers.end(); ++it)
    {
        if(*it == person)
        {
            _observers.erase(it);
            break;
        }
    }
}

void Party::RemoveChild(Person *person)
{
    for(auto it = _children.begin(); it != _children.end(); ++it)
    {
        if(*it == person)
        {
            _children.erase(it);
            break;
        }
    }
}

int Party::GetAffectedChildren()
{
    // TODO - Use party member pointers and party member type to identify affected children.
    return _children.size();
}
