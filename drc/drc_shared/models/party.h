#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include <QTextCursor>
#include <QTextDocument>
#include "drctypes.h"
#include "Person.h"
#include "DBBaseObject.h"

/*!
 * \brief The Party class
 */
class Party : public DBBaseObject
{
public:
    Party();

    //Virtual overrides
    /*!
     * \brief Parse
     * \return
     */
    QString Parse();
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
     * \brief SetPrimary
     * \param primary
     */
    void SetPrimary(Person *primary) { _primary = primary; }
    /*!
     * \brief GetPrimary
     * \return
     */
    Person *GetPrimary() { return _primary; }
    /*!
     * \brief SetObservers
     * \param observers
     */
    void SetObservers(PersonVector& observers) { _observers = observers; }
    /*!
     * \brief GetObservers
     * \return
     */
    PersonVector& GetObservers() { return _observers; }
    /*!
     * \brief SetChildren
     * \param children
     */
    void SetChildren(PersonVector& children) { _children = children; }
    /*!
     * \brief GetChildren
     * \return
     */
    PersonVector& GetChildren() { return _children; }
    /*!
     * \brief SetType
     * \param type
     */
    void SetType(PartyTypes type) { _type = type; }
    /*!
     * \brief SetAttorney
     * \param attorney
     */
    void SetAttorney(Person attorney) { _attorney = attorney; }
    /*!
     * \brief GetAttorney
     * \return
     */
    Person& GetAttorney() { return _attorney; }
    /*!
     * \brief GetSpanishRequired
     * \return
     */
    bool GetSpanishRequired();
    /*!
     * \brief AddObserver
     * \param person
     */
    void AddObserver(Person* person) { if(person) _observers.push_back(person); }
    /*!
     * \brief RemoveObserver
     * \param person
     */
    void RemoveObserver(Person* person);
    /*!
     * \brief AddChild
     * \param person
     */
    void AddChild(Person* person) { if(person) _children.push_back(person); }
    /*!
     * \brief RemoveChild
     * \param person
     */
    void RemoveChild(Person* person);
    /*!
     * \brief GetAffectedChildren
     * \return
     */
    int GetAffectedChildren();
    /*!
     * \brief GetTotalChildren
     * \return
     */
    int GetTotalChildren() { return _children.size(); }

    // Test Data - Fill the object with test values in every field.
    /*!
     * \brief SampleData
     * \return
     */
    static Party* SampleData();
    /*!
     * \brief BuildToPDF
     * \param cursor
     */
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
