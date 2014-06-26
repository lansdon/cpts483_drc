
#include "DRCClient.h"
#include "ui_DRCClient.h"


// GUI STUFF
#include <QGridLayout>
#include <QTabWidget>
#include "fruitnameform.h"
#include "loginform.h"
#include "queryform.h"
#include "Mediator.h"
#include "drctypes.h"
#include "searchwizard/searchwizard.h"
#include "toolbarmanager.h"
#include "mediationbrowser.h"
#include "mptoolbox.h"

// DRC COMPONENTS
#include "drcbl.h"
#include "drcdb.h"

// MISC
#include <QDebug>
#include <QDockWidget>

DRCClient::DRCClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DRCClient)
    , _browserDock(nullptr)
{
    ui->setupUi(this);
    // set up a seed for any random numbers generated with qrand()
    qsrand( QDateTime::currentMSecsSinceEpoch()/1000);

    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);

    setCentralWidget(new LoginForm(this));

    // Listen for
    Mediator::Register(MKEY_GUI_ENABLE_MENUS, [this](MediatorArg arg){SetMenuBarEnabled();});
    Mediator::Register(MKEY_GUI_ENABLE_MENUS, [this](MediatorArg arg){SetMenuHelpEnabled();});
    Mediator::Register(MKEY_GUI_DISABLE_MENUS, [this](MediatorArg arg){SetMenuBarDisabled();});
    Mediator::Register(MKEY_GUI_DISABLE_MENUS, [this](MediatorArg arg){SetMenuHelpDisabled();});
    Mediator::Register(MKEY_GUI_SHOW_ADMIN, [this](MediatorArg arg){SetMenuAdminShow();});
    Mediator::Register(MKEY_GUI_HIDE_ADMIN, [this](MediatorArg arg){SetMenuAdminHide();});
    Mediator::Register(MKEY_GUI_SHOW_MEDIATION_BROWSER, [this](MediatorArg arg){ShowMediationBrowser();});
    Mediator::Register(MKEY_GUI_SHOW_SESSIONS_BROWSER, [this](MediatorArg arg){ShowSessionBrowser();});

    // Toolbar manager setup
    ToolbarManager::Instance().SetToolbar(ui->toolBar);
    ToolbarManager::Instance().Clear();

    // Disable Menus Until Logged In
    SetMenusEnabled(true, false);
}

DRCClient::~DRCClient()
{
   delete ui;
}

void DRCClient::SetMenusEnabled(bool enableMenus, bool showAdmin)
{
    ui->menuBar->setEnabled(enableMenus);
    ui->menuHelp->setEnabled(enableMenus);
    ui->toolBar->setEnabled(enableMenus);
    ui->menuAdmin->menuAction()->setVisible(showAdmin);
}

void DRCClient::SetMenuBarEnabled()
{
    ui->menuBar->setEnabled(true);
}

void DRCClient::SetMenuHelpEnabled()
{
    ui->menuHelp->setEnabled(true);
}

void DRCClient::SetMenuBarDisabled()
{
    ui->menuBar->setEnabled(false);
}

void DRCClient::SetMenuHelpDisabled()
{
    ui->menuHelp->setEnabled(false);
}

void DRCClient::SetMenuAdminShow()
{
    ui->menuAdmin->menuAction()->setVisible(true);
}

void DRCClient::SetMenuAdminHide()
{
    ui->menuAdmin->menuAction()->setVisible(false);
}

void DRCClient::on_actionNew_Fruit_Submission_triggered()
{
    setCentralWidget(new FruitNameForm(this));
}

void DRCClient::on_actionNew_Form_triggered()
{
//    setCentralWidget(new IntakeForm(this));
}

void DRCClient::on_actionNew_search_form_triggered()
{
 //   setCentralWidget(new SearchWizard(this));
    setCentralWidget(new QueryForm(this));
}

void DRCClient::on_actionOpen_mediation_view_triggered()
{
    LoadMediationProcessView();
}

void DRCClient::on_actionMediation_Process_triggered()
{
    setCentralWidget(new MediationProcessView());
}

void DRCClient::on_actionFruit_Test_triggered()
{
    setCentralWidget(new FruitNameForm(this));
}

void DRCClient::on_actionLogout_User_triggered()
{
    SetMenusEnabled(false, false);
    delete _mediationProcessView;
    _mediationProcessView = nullptr;
    setCentralWidget(new LoginForm());
}



void DRCClient::on_mediationProcessSelected(MediationProcess* process)
{
    qDebug() << "DRC Client - on_mediationProcessSelected!";

    LoadMediationProcessView(process);
}

void DRCClient::LoadMediationProcessView(MediationProcess* process)
{
    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(process);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::ShowNotesBrowser()
{

}

void DRCClient::ShowSessionBrowser()
{

}

void DRCClient::ShowMediationBrowser()
{
    bool shouldDisplayTable = _browserDock ? !_browserDock->isVisible() : true;

    // Clear existing table everytime.
    if(_browserDock)
    {
        if(_browserDock->isVisible())
            _browserDock->close();
        removeDockWidget(_browserDock);
        _browserDock = nullptr;
    }

    if(shouldDisplayTable)
    {
        _browserDock = new QDockWidget("Browser Toolbox", this);
        MPToolBox* mpToolbox = new MPToolBox(_browserDock);
//        MediationBrowser* mpTable = new MediationBrowser(_browserDock);
        connect(mpToolbox, SIGNAL(MPSelected(MediationProcess*)), this, SLOT(on_mediationProcessSelected(MediationProcess*)));
        _browserDock->setWidget(mpToolbox);
        addDockWidget(Qt::RightDockWidgetArea, _browserDock);
    }
}
