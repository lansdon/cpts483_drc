#ifndef SESSIONSTABLEFORM_H
#define SESSIONSTABLEFORM_H

#include <QWidget>
#include <QTableWidget>
#include "drctypes.h"
#include "Mediator.h"

namespace Ui {
class SessionsBrowser;
}

/*!
 * \brief The SessionsBrowser class
 */
class SessionsBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit SessionsBrowser(QWidget *parent = 0, MediationSessionVector* sessions = nullptr);
    ~SessionsBrowser();

    /*!
     * \brief SetSessions
     * \param sessions
     */
    void SetSessions(MediationSessionVector* sessions);
    /*!
     * \brief SetSessionsEvent
     * \param arg
     */
    void SetSessionsEvent(MediatorArg arg);

protected slots:
    /*!
     * \brief on_tableWidget_itemSelectionChanged
     */
    void on_tableWidget_itemSelectionChanged();

private slots:
    /*!
     * \brief on_addSessionBtn_clicked
     */
    void on_addSessionBtn_clicked();
    /*!
     * \brief on_delSessionBtn_clicked
     */
    void on_delSessionBtn_clicked();

private:
    Ui::SessionsBrowser *ui;

    MediationSessionVector* _sessions;

    // Sessions Table
    QTableWidget* _sessionTable;
    /*!
     * \brief configSessionTable
     */
    void configSessionTable();
    /*!
     * \brief PopulateSessionTable
     */
    void PopulateSessionTable();

    MediatorId _setSessionsCallback;

};

#endif // SESSIONSTABLEFORM_H
