#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include <QTextCursor>
#include <QTextDocument>
#include "drctypes.h"
#include "Person.h"
#include "DBBaseObject.h"


class Party : public DBBaseObject
{
public:
    Party();

    //Virtual overrides
    QString Parse();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    QString GetIdRowName();

    // Accessors
    void SetPrimary(Person *primary) { _primary = primary; }
    Person *GetPrimary() { return _primary; }
    void SetObservers(PersonVector& observers) { _observers = observers; }
    PersonVector& GetObservers() { return _observers; }
    void SetChildren(PersonVector& children) { _children = children; }
    PersonVector& GetChildren() { return _children; }
    void SetType(PartyTypes type) { _type = type; }
    void SetAttorney(Person attorney) { _attorney = attorney; }
    Person& GetAttorney() { return _attorney; }
    bool GetSpanishRequired();

    void AddObserver(Person* person) { if(person) _observers.push_back(person); }
    void RemoveObserver(Person* person);
    void AddChild(Person* person) { if(person) _children.push_back(person); }
    void RemoveChild(Person* person);
    int GetAffectedChildren();
    int GetTotalChildren() { return _children.size(); }
    // Test Data - Fill the object with test values in every field.
    static Party* SampleData();

    void BuildToPDF(QTextCursor &cursor);

private:
    QTextCharFormat _headerFormat;
    QTextCharFormat _tableTextFormat;

    Person *_primary;
    PersonVector _observers;
    PersonVector _children;
    Person _attorney;
    PartyTypes _type;
};

#endif // PARTY_H
