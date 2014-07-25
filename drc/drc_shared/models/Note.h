#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <QTextCursor>
#include "DBBaseObject.h"

/*!
 * \brief The Note class
 */
class Note : public DBBaseObject
{
private:
    QString _message;
    int _sessionId;
    int _mediationId;

    // Text Formatters
    QTextCharFormat _headerFormat;
    QTextCharFormat _tableTextFormat;
    QTextTableCellFormat _tableCellBlue;
    QTextTableCellFormat _tableIndexDark;
    QTextTableCellFormat _tableIndexLight;

public:
    /*!
     * \brief Note
     * \param message
     */
    Note(QString message = "");
    /*!
     * \brief SetMessage
     * \param message
     */
    void SetMessage(QString message);
    /*!
     * \brief SetSessionId
     * \param sessionId
     */
    void SetSessionId(int sessionId);
    /*!
     * \brief SetMediationId
     * \param mediationId
     */
    void SetMediationId(int mediationId);
    /*!
     * \brief GetMessage
     * \return
     */
    QString GetMessage();
    /*!
     * \brief GetSessionId
     * \return
     */
    int GetSessionId();
    /*!
     * \brief GetmediationId
     * \return
     */
    int GetmediationId();

    // Base Class Virtual Overrides
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
     * \brief BuildToPDF
     * \param cursor
     */
    void BuildToPDF(QTextCursor& cursor);

};

#endif // NOTEFORM_H
