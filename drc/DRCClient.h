#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include <QMainWindow>
#include <QString>
#include "drcbl.h"
#include "drcdb.h"
#include "mediationprocessview.h"
#include "Mock_Server/mock_server.h"
#include "drc_shared/CurrentUser.h"
#include "mptoolbox.h"
#include "mpfilemaker.h"
#include "Mediator.h"

namespace Ui {
class DRCClient;
}
/*!
 * \brief The DRCClient class
 */
class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

    // This will enable our GUI menus
    /*!
     * \brief SetMenuBarEnabled
     */
    void SetMenuBarEnabled();
    /*!
     * \brief SetMenuHelpEnabled
     */
    void SetMenuHelpEnabled();

    // This will disable our GUI menus
    /*!
     * \brief SetMenuBarDisabled
     */
    void SetMenuBarDisabled();
    /*!
     * \brief SetMenuHelpDisabled
     */
    void SetMenuHelpDisabled();

    // This will set our Admin menu options to visible
    /*!
     * \brief SetMenuAdminShow
     */
    void SetMenuAdminShow();

    // This will set our Admin menu options to invisible
    /*!
     * \brief SetMenuAdminHide
     */
    void SetMenuAdminHide();
    /*!
     * \brief ShowMainMenu
     */
    void ShowMainMenu();

private slots:
    /*!
     * \brief on_actionNew_search_form_triggered
     */
    void on_actionNew_search_form_triggered();
    /*!
     * \brief on_actionOpen_mediation_view_triggered
     */
    void on_actionOpen_mediation_view_triggered();
    /*!
     * \brief on_actionMediation_Process_triggered
     */
    void on_actionMediation_Process_triggered();
    /*!
     * \brief on_actionLogout_User_triggered
     */
    void on_actionLogout_User_triggered();
    /*!
     * \brief on_actionNew_2_triggered
     */
    void on_actionNew_2_triggered();
    /*!
     * \brief on_actionAdd_1_MP_sample_triggered
     */
    void on_actionAdd_1_MP_sample_triggered();
    /*!
     * \brief on_actionAdd_to_vector_triggered
     */
    void on_actionAdd_to_vector_triggered();
    /*!
     * \brief on_actionSave_to_file_triggered
     */
    void on_actionSave_to_file_triggered();
    /*!
     * \brief on_actionLoad_from_file_triggered
     */
    void on_actionLoad_from_file_triggered();
    /*!
     * \brief on_actionAdd_5_MP_samples_triggered
     */
    void on_actionAdd_5_MP_samples_triggered();
    /*!
     * \brief on_actionManage_Users_triggered
     */
    void on_actionManage_Users_triggered();
    /*!
     * \brief on_actionConnect_to_Remote_DB_triggered
     */
    void on_actionConnect_to_Remote_DB_triggered();
    /*!
     * \brief on_actionFindMediation_triggered
     */
    void on_actionFindMediation_triggered();

    void on_actionMonthly_Report_triggered();

    void on_actionRes_Wa_Report_triggered();

public slots:
    /*!
     * \brief ShowSessionBrowser
     */
    void ShowSessionBrowser();
    /*!
     * \brief ShowMediationBrowser
     */
    void ShowMediationBrowser();
    /*!
     * \brief ShowNotesBrowser
     */
    void ShowNotesBrowser();
    /*!
     * \brief ShowResWaReport
     */
    void ShowResWaReport();
    /*!
     * \brief ShowMonthlyReport
     */
    void ShowMonthlyReport();
    /*!
     * \brief LoadEvaluationView
     */
    void LoadEvaluationView();
    /*!
     * \brief send_mediation_vector
     */
    void send_mediation_vector();
    /*!
     * \brief on_mediationProcessSelected
     * \param process
     */
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
    /*!
     * \brief LoadMediationProcessView
     * \param process
     */
    void LoadMediationProcessView(MediationProcess* process = nullptr);
    // Dock views
    QDockWidget* _browserDock;

    /*!
     * \brief ShowBrowser
     * \param browserType
     */
    void ShowBrowser(MPBrowserTypes browserType);
    /*!
     * \brief SetMainView
     * \param widget
     */
    void SetMainView(QWidget* widget);
    /*!
     * \brief SetMenusEnabled
     * \param enableMenus
     * \param showAdmin
     */
    void SetMenusEnabled(bool enableMenus, bool showAdmin);

    //for file load save
    MediationProcessVector *_mediationProcessVector;
    MPFileMaker _filemaker;

    /*!
     * \brief saveMPEvent
     * \param arg
     */
    void saveMPEvent(MediatorArg arg);
    /*!
     * \brief LoadDBPathFromFile
     * \return
     */
    QString LoadDBPathFromFile();
};

#endif // DRCClient_H
