
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

// DRC COMPONENTS
#include "drcbl.h"
#include "drcdb.h"

// MISC
#include <QDebug>

DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient)
{
    ui->setupUi(this);
    // set up a seed for any random numbers generated with qrand()
    qsrand( QDateTime::currentMSecsSinceEpoch()/1000);



    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);

    setCentralWidget(new LoginForm(this));

    // Listen for
    Mediator::Register(MKEY_CURRENT_USER_CHANGED, [this](MediatorArg arg){CurrentUserChanged(arg);});

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

// This will update the gui menus based on current user status.
void DRCClient::CurrentUserChanged(MediatorArg arg)
{
    bool isAdmin = false;
    bool showMenus = false;

    User* tmpUser = arg.getArg<User*>();
    if(arg.IsSuccessful() && tmpUser)
    {
        isAdmin = (tmpUser->GetType() == USER_T_SUPER_USER || tmpUser->GetType() == USER_T_ADMIN);
        showMenus = (isAdmin || tmpUser->GetType() == USER_T_NORMAL);
    }
    SetMenusEnabled(showMenus, isAdmin);
}

void DRCClient::SetMenusEnabled(bool enableMenus, bool showAdmin)
{
    ui->menuBar->setEnabled(enableMenus);
    ui->menuHelp->setEnabled(enableMenus);
    ui->toolBar->setEnabled(enableMenus);
    ui->menuAdmin->menuAction()->setVisible(showAdmin);
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
    setCentralWidget(new MediationProcessView());
}

void DRCClient::on_actionMediation_Process_triggered()
{
    setCentralWidget(new MediationProcessView());
}

void DRCClient::on_actionFruit_Test_triggered()
{
    setCentralWidget(new FruitNameForm(this));
}

void DRCClient::on_actionLock_Account_triggered()
{
    SetMenusEnabled(false, false);
    setCentralWidget(new LoginForm());
}

void DRCClient::on_actionLogout_User_triggered()
{
    SetMenusEnabled(false, false);
    setCentralWidget(new LoginForm());
}
