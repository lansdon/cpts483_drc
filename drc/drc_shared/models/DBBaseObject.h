#ifndef DBBASEOBJECT_H
#define DBBASEOBJECT_H

#include <QString>
#include <QDateTime>

/*!
 * \brief The DBBaseObject class
 */
class DBBaseObject
{
protected:
    unsigned int m_id;      // properties shared by all db objects
    QDateTime m_created;    // properties shared by all db objects
    QDateTime m_updated;    // properties shared by all db objects

public:
    DBBaseObject() : m_id(0), m_created(QDateTime::currentDateTime()), m_updated(m_created) {}
    //Outputs field data into a SQLite appropriate string format
    //for insertion into a database.

    //Object is still subject to change pending discussion with DB Team.
    virtual QString Parse(void) = 0;

    virtual QString UpdateParse(void) = 0;

    virtual QString ColumnNames(void) = 0;

    virtual QString GetIdRowName(void) = 0;

    unsigned int GetId() { return m_id; }
    void SetId(unsigned int id) { m_id = id; }

    QDateTime GetCreatedDate() { return m_created; }
    void SetCreatedDate(QDateTime created) { m_created = created; }

    QDateTime GetUpdatedDate() { return m_updated; }
    void SetUpdatedDate(QDateTime updated) { m_updated = updated; }
    void SetUpdatedDate() { m_updated = QDateTime::currentDateTime(); } // helper for current date

    virtual QString table() = 0;

    //virtual QString DuplicateQuery() = 0;

    //virtual QString SearchQuery() = 0;
};


#endif // DBBASEOBJECT_H
