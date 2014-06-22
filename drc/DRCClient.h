#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include <QMainWindow>
#include <QString>
#include "drcbl.h"
#include "drcdb.h"
#include "fruitnameform.h"
#include "mediationprocessview.h"
#include "Mock_Server/mock_server.h"
#include "drc_shared/CurrentUser.h"

namespace Ui {
class DRCClient;
}

class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

    // This will enable our GUI menus
    void SetMenuBarEnabled();
    void SetMenuHelpEnabled();

    // This will disable our GUI menus
    void SetMenuBarDisabled();
    void SetMenuHelpDisabled();

    // This will set our Admin menu options to visible
    void SetMenuAdminShow();

    // This will set our Admin menu options to invisible
    void SetMenuAdminHide();

private slots:

    void on_actionNew_Fruit_Submission_triggered();

    void on_actionNew_Form_triggered();

    void on_actionNew_search_form_triggered();

    void on_actionOpen_mediation_view_triggered();

    void on_actionMediation_Process_triggered();

    void on_actionFruit_Test_triggered();

    void on_actionLock_Account_triggered();

    void on_actionLogout_User_triggered();

public slots:

    void on_toggle_mediation_table_dock();

    void on_mediationProcessSelected(MediationProcess* process);

private:
    Ui::DRCClient *ui;

    // Important!! These objects are automatically initialized.
    // They need to be instantiated at startup to register events properly.
    DRCBL _bl;  // Business Logic
    DRCDB _db;  // Database
    Mock_Server _ms; // mock server for gui testing

    // Primary Views
    MediationProcessView* _mediationProcessView;
    void LoadMediationProcessView(MediationProcess* process = nullptr);
    // Dock views
    QDockWidget* _mediationTableDock;

    void SetMainView(QWidget* widget);
    void SetMenusEnabled(bool enableMenus, bool showAdmin);

};

#endif // DRCClient_H
