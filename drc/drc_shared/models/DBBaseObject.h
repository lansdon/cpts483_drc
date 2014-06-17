#ifndef DBBASEOBJECT_H
#define DBBASEOBJECT_H

#include <QString>
#include <QDateTime>

class DBBaseObject
{
protected:
    unsigned int m_id;      // properties shared by all db objects
    QDateTime m_created;    // properties shared by all db objects
    QDateTime m_updated;    // properties shared by all db objects

public:
    //Outputs field data into a SQLite appropriate string format
    //for insertion into a database.

    //Object is still subject to change pending discussion with DB Team.
    virtual QString Parse(void) = 0;

    QDateTime GetCreated() { return m_created; }
    QDateTime GetUpdated() { return m_updated; }

    unsigned int GetId() { return m_id; }
    void SetId(unsigned int id) { m_id = id; }

    QDateTime GetCreatedDate() { return m_created; }
    void SetCreatedDate(QDateTime created) { m_created = created; }

    QDateTime GetUpdatedDate() { return m_updated; }
    void SetUpdatedDate(QDateTime updated) { m_updated = updated; }
    void SetUpdatedDate() { m_updated = QDateTime::currentDateTime(); } // helper for current date

    virtual QString table() = 0;

    virtual QString DuplicateQuery() = 0;

    virtual QString SearchQuery() = 0;
};


#endif // DBBASEOBJECT_H
