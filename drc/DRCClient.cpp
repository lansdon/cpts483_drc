
#include "DRCClient.h"
#include "ui_DRCClient.h"


// GUI STUFF
#include <QGridLayout>
#include <QTabWidget>
#include "intakeform.h"
#include "fruitnameform.h"
#include "intakeform.h"
#include "loginform.h"
#include "queryform.h"
#include "Mediator.h"
#include "UserType.h"

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

    setCentralWidget(new LoginForm(this));

    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);

    // Listen for
    Mediator::Register(MKEY_CURRENT_USER_CHANGED, [this](MediatorArg arg){CurrentUserChanged(arg);});

    // Disable Menus Until Logged In
    SetMenusEnabled(false, false);
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
        isAdmin = (tmpUser->GetType() == SUPER_USER || tmpUser->GetType() == ADMIN);
        showMenus = (isAdmin || tmpUser->GetType() == NORMAL_USER);
    }
    SetMenusEnabled(showMenus, isAdmin);
}

void DRCClient::SetMenusEnabled(bool enableMenus, bool showAdmin)
{
    ui->menuBar->setEnabled(enableMenus);
//    ui->menuHelp->setEnabled(enableMenus);
//    ui->menuHelp->setEnabled(enableMenus);
//    ui->menuHelp->setEnabled(enableMenus);
//    ui->menuHelp->setEnabled(enableMenus);
//    ui->menuHelp->setEnabled(enableMenus);

    if(enableMenus)
    {
        ui->menuHelp->setEnabled(enableMenus);
        if(showAdmin)
        {

        }
    }
    else
    {

    }
}


void DRCClient::on_actionNew_Fruit_Submission_triggered()
{
    setCentralWidget(new FruitNameForm(this));
}

void DRCClient::on_actionNew_Form_triggered()
{
    setCentralWidget(new IntakeForm(this));
}

void DRCClient::on_actionNew_search_form_triggered()
{
    setCentralWidget(new QueryForm());
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
