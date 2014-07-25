#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"
#include <QString>
#include "drctypes.h"
#include "Crypto/SHA256_Crypto.h"

/*!
 * \brief The User class
 */
class User : public DBBaseObject
{
private:
	QString m_userName;
	QString m_password;
    UserTypes m_type;

public:
	User();
    /*!
     * \brief User
     * \param name
     * \param pass
     * \param type
     */
    User(QString name, QString pass, UserTypes type = USER_T_NORMAL);
    /*!
     * \brief GetName
     * \return
     */
    QString GetName(void);
    /*!
     * \brief SetName
     * \param name
     */
    void SetName(QString name);
    /*!
     * \brief GetPass
     * \return
     */
    QString GetPass(void);
    /*!
     * \brief SetPassword
     * \param password
     */
    void SetPassword(QString password);
    /*!
     * \brief GetType
     * \return
     */
    UserTypes GetType(void);
    /*!
     * \brief SetType
     * \param Type
     */
    void SetType(UserTypes Type);
    /*!
     * \brief GetTypeString
     * \return
     */
    QString GetTypeString(void);
    /*!
     * \brief Parse
     * \return
     */
    QString Parse(void);
    /*!
     * \brief UpdateParse
     * \return
     */
    QString UpdateParse();
    /*!
     * \brief GetIdRowName
     * \return
     */
    QString GetIdRowName();
    /*!
     * \brief table
     * \return
     */
    QString table(void);
    /*!
     * \brief DuplicateQuery
     * \return
     */
    QString DuplicateQuery(void);
    /*!
     * \brief SearchQuery
     * \return
     */
    QString SearchQuery(void);
};

#endif
