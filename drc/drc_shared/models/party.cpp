#include "party.h"
#include "Person.h"
#include "persondetailsform.h"
#include "drctypes.h"
#include <sstream>
#include <QDebug>

Party::Party()
{
    _primary = new Person();
}

QString Party::Parse()
{
#warning TODO - Parse() UNIMPLEMENTED!!!!
    return "";
}

QString Party::UpdateParse()
{
#warning TODO - UpdateParse() UNIMPLEMENTED!!!!
    return "";

}

QString Party::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!
    return "";

}

QString Party::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";

}

QString Party::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";

}

QString Party::GetIdRowName()
{
#warning TODO - GetIdRowName() UNIMPLEMENTED!!!!
    return "";

}

void Party::BuildToPDF(QTextCursor &cursor)
{
    cursor.movePosition(QTextCursor::End);

    QString Name = "\nFirst:\t";
    Name += _primary->getFirstName();
    Name += "\tMiddle:\t";
    Name += _primary->getMiddleName();
    Name += "\tLast:\t";
    Name += _primary->getLastName();
    cursor.insertText(Name, _tableTextFormat);

    QString StreetUnit = "\nStreet:\t";
    StreetUnit += _primary->getStreet();
    StreetUnit += "\tUnit:\t";
    StreetUnit += _primary->getUnit();
    cursor.insertText(StreetUnit, _tableTextFormat);

    QString CityState = "\nCity:\t";
    CityState += _primary->getCity();
    CityState += "\tState:\t";
    CityState += _primary->getState();
    cursor.insertText(CityState, _tableTextFormat);

    QString CountyZip = "\nCount:\t";
    CountyZip += StringForCountyIds(_primary->getCounty());
    CountyZip += "\tZip:\t";
    CountyZip += _primary->getZip();
    cursor.insertText(CountyZip, _tableTextFormat);

    cursor.insertText("\n===Phone and Email===");

    QString PrimaryExt = "\nPrimary:\t";
    PrimaryExt += _primary->getPrimaryPhone();
    PrimaryExt += "\tExt:\t";
    PrimaryExt += _primary->getPrimaryPhoneExt();
    cursor.insertText(PrimaryExt, _tableTextFormat);

    QString SecondaryExt = "\nSecondary:\t";
    SecondaryExt += _primary->getSecondaryPhone();
    SecondaryExt += "\tExt:\t";
    SecondaryExt += _primary->getSecondaryPhoneExt();
    cursor.insertText(SecondaryExt, _tableTextFormat);

    QString Email = "\nEmail:\t";
    Email += _primary->getEmail();
    cursor.insertText(Email, _tableTextFormat);

    QString AdultsChildrenInHome = "\nAdults in Home:\t";
    AdultsChildrenInHome += QString::number(_primary->getNumberInHousehold());
    AdultsChildrenInHome += "\tChildren in Home:\t";
    AdultsChildrenInHome += QString::number(_primary->getNumberChildrenInHousehold());
    cursor.insertText(AdultsChildrenInHome, _tableTextFormat);

    QString AttorneyNamePhone = "\nAttorney Name:\t";
    AttorneyNamePhone += _primary->getAttorney();
    AttorneyNamePhone += "\tPhone:\t";
    AttorneyNamePhone += _primary->getAttorneyPhone();
    cursor.insertText(AttorneyNamePhone, _tableTextFormat);

    QString AttorneyEmail = "\n\t\tEmail:\t";
    AttorneyEmail += _primary->getAttorneyEmail();
    cursor.insertText(AttorneyEmail, _tableTextFormat);

    QString AssistantNamePhone = "\nAssistant Name:\t";
    AssistantNamePhone += _primary->getAssistantName();
    AssistantNamePhone += "\tPhone:\t";
    AssistantNamePhone += _primary->getAssistantPhone();
    cursor.insertText(AssistantNamePhone, _tableTextFormat);

    QString AssistantEmail = "\n\t\tEmail:\t";
    AssistantEmail += _primary->getAssistantEmail();
    cursor.insertText(AssistantEmail, _tableTextFormat);
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

    result->SetPrimary(Person::SampleData());
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

bool Party::GetSpanishRequired()
{
    bool result = rand() % 2;

    // Todo Check all party members!

    return result;
}
