#ifndef SESSIONSTABLEFORM_H
#define SESSIONSTABLEFORM_H

#include <QWidget>
#include <QTableWidget>
#include "drctypes.h"
#include "Mediator.h"

namespace Ui {
class SessionsTableForm;
}

class SessionsTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit SessionsTableForm(QWidget *parent = 0, MediationSessionVector* sessions = nullptr);
    ~SessionsTableForm();

    void SetSessions(MediationSessionVector* sessions);
    void SetSessionsEvent(MediatorArg arg);

protected slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::SessionsTableForm *ui;

    MediationSessionVector* _sessions;

    // Sessions Table
    QTableWidget* _sessionTable;
    void configSessionTable();
    void PopulateSessionTable();

};

#endif // SESSIONSTABLEFORM_H
