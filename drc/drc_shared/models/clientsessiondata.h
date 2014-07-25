#ifndef CLIENTSESSIONDATA_H
#define CLIENTSESSIONDATA_H

#include <QString>
#include <QTextCursor>

#include "DBBaseObject.h"
/*!
 * \brief The ClientSessionData class
 */
class ClientSessionData : public QObject, public DBBaseObject
{
public:
    ClientSessionData();

    // getters
    /*!
     * \brief getIncome() will return the income of a party.
     * \return QString
     */
    QString getIncome() const { return income; }
    /*!
     * \brief getFee() will return the fee of a specific party.
     * \return QString
     */
    QString getFee() const { return fee; }
    /*!
     * \brief getPaid() will return a bool to identify if a session is paid.
     * \return bool
     */
    bool getPaid() const { return paid; }
    /*!
     * \brief getAttySaidAttend() will return a bool to identify if
     *                            attorney is to be present for a session.
     * \return bool
     */
    bool getAttySaidAttend() const { return attySaidAttend; }
    /*!
     * \brief getAttyDidAttend() will return a bool depending on
     *                           whether or not attorney attended.
     * \return bool
     */
    bool getAttyDidAttend() const { return attyDidAttend; }
    /*!
     * \brief getSupport() will return number of support people
     *                     for a specific party.
     * \return uint
     */
    uint getSupport() const { return support; }
    /*!
     * \brief getAtTable() returns a bool if party attended or not.
     * \return bool
     */
    bool getAtTable() const { return atTable; }
    /*!
     * \brief getOnPhone() returns a bool if party attended by phone or not.
     * \return bool
     */
    bool getOnPhone() const { return onPhone; }

    // setters
    /*!
     * \brief setIncome() will set income for a party.
     * \param value
     */
    void setIncome(QString value) { income = value; }
    /*!
     * \brief setFee() will set fee for a party.
     * \param value
     */
    void setFee(QString value) { fee = value; }
    /*!
     * \brief setPaid()
     * \param value
     */
    void setPaid(bool value) { paid = value; }
    /*!
     * \brief setAttySaidAttend()
     * \param value
     */
    void setAttySaidAttend(bool value) { attySaidAttend = value; }
    /*!
     * \brief setAttyDidAttend()
     * \param value
     */
    void setAttyDidAttend(bool value) { attyDidAttend = value; }
    /*!
     * \brief setSupport()
     * \param value
     */
    void setSupport(uint value) { support = value; }
    /*!
     * \brief setAtTable()
     * \param value
     */
    void setAtTable(bool value) { atTable = value; }
    /*!
     * \brief setOnPhone()
     * \param value
     */
    void setOnPhone(bool value) { onPhone = value; }

    //Virtual overrides
    QString Parse();
    QString ColumnNames();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();
    QString GetIdRowName();

    //helpers
    bool isPaid() const;
    bool isNoFee() const;
    void print(QTextCursor &cursor);

public slots:
    void on_atty_will_attend(bool value);
    void on_atty_did_attend(bool value);
    void on_support(uint value);
private:
    QString income, fee;
    bool paid, attySaidAttend, attyDidAttend, atTable, onPhone;
    uint support;
};

#endif // CLIENTSESSIONDATA_H
