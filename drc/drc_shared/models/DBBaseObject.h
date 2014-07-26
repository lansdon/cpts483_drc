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

    /*!
     * \brief Parse
     * \return
     */
    virtual QString Parse(void) = 0;
    /*!
     * \brief UpdateParse
     * \return
     */
    virtual QString UpdateParse(void) = 0;

    virtual QString ColumnNames(void) = 0;

    /*!
     * \brief GetIdRowName
     * \return
     */
    virtual QString GetIdRowName(void) = 0;
    /*!
     * \brief GetId
     * \return
     */
    unsigned int GetId() { return m_id; }
    /*!
     * \brief SetId
     * \param id
     */
    void SetId(unsigned int id) { m_id = id; }
    /*!
     * \brief GetCreatedDate
     * \return
     */
    QDateTime GetCreatedDate() { return m_created; }
    /*!
     * \brief SetCreatedDate
     * \param created
     */
    void SetCreatedDate(QDateTime created) { m_created = created; }
    /*!
     * \brief GetUpdatedDate
     * \return
     */
    QDateTime GetUpdatedDate() { return m_updated; }
    /*!
     * \brief SetUpdatedDate
     * \param updated
     */
    void SetUpdatedDate(QDateTime updated) { m_updated = updated; }
    /*!
     * \brief SetUpdatedDate
     */
    void SetUpdatedDate() { m_updated = QDateTime::currentDateTime(); } // helper for current date
    /*!
     * \brief table
     * \return
     */
    virtual QString table() = 0;
};

#endif // DBBASEOBJECT_H
