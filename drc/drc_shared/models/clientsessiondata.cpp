#include "clientsessiondata.h"
/*!
 * \brief ClientSessionData::ClientSessionData() is the constructor
 *
 */
ClientSessionData::ClientSessionData()
{
    paid = attyDidAttend = attySaidAttend = atTable = onPhone = false;
    support = 0;
}

QString ClientSessionData::Parse()
{
#warning TODO - Parse() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::UpdateParse()
{
#warning TODO - UpdateParse() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::GetIdRowName()
{
#warning TODO - GetIdRowName() UNIMPLEMENTED!!!!
    return "";
}

/*!
 * \brief ClientSessionData::on_atty_will_attend() will set the
 *                           AttySaidAttend variable
 * \param value
 */
void ClientSessionData::on_atty_will_attend(bool value)
{
    setAttySaidAttend(value);
}

/*!
 * \brief ClientSessionData::on_atty_did_attend() will set the
 *                           AttyDidAttend variable
 * \param value
 */
void ClientSessionData::on_atty_did_attend(bool value)
{
    setAttyDidAttend(value);
}

/*!
 * \brief ClientSessionData::on_support() will set number of Supports for a session
 * \param value
 */
void ClientSessionData::on_support(uint value)
{
    setSupport(value);
}

/*!
 * \brief ClientSessionData::isPaid() will check if fee is paid off.
 * \return bool
 *
 * Will return true if isNoFee is false and paid is true, else it returns false.
 */
bool ClientSessionData::isPaid() const
{
    return ((!isNoFee()) && paid);
}

/*!
 * \brief ClientSessionData::isNoFee() will check if there is a fee.
 * \return bool
 *
 * Will return true if there is no fee or if the fee is 0 anything else will return false.
 */
bool ClientSessionData::isNoFee() const
{
    return (fee.isEmpty() || (fee.toDouble() == 0));
}

void ClientSessionData::print(QTextCursor &cursor)
{      
    cursor.insertText("\n\tFee: " + fee);
    cursor.insertText("\n\tIncome: " + income);
    cursor.insertText("\n\tPaid: ");
    if(paid)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText("\tAt Table: ");
    if(atTable)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText("\n\tSupport: " + QString::number(support));
    cursor.insertText("\n\tAttorney said they would attend: ");
    if(attySaidAttend)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText("\n\tAttorney did attend: ");
    if(attyDidAttend)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText("\n");

}
