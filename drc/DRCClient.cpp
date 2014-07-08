
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "mpfilemaker.h"


// GUI STUFF
#include <QGridLayout>
#include <QTabWidget>
#include "loginform.h"
#include "queryform.h"
#include "Mediator.h"
#include "drctypes.h"
#include "searchwizard/searchwizard.h"
#include "toolbarmanager.h"
#include "mediationbrowser.h"
#include "mptoolbox.h"
#include "mainmenuform.h"
#include "manageusers.h"
#include "reswareportform.h"

// DRC COMPONENTS
#include "drcbl.h"
#include "drcdb.h"

// MISC
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>

const QString DBPATH_FILE = "dbpath.txt";
const QString DB_DEFAULT_PATH = "drc_db.db3";


DRCClient::DRCClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DRCClient)
    , _browserDock(nullptr)
{
    ui->setupUi(this);
    // set up a seed for any random numbers generated with qrand()
    qsrand( QDateTime::currentMSecsSinceEpoch()/1000);

    // Check for a saved database path... Load the default otherwise.
    _db.LoadDatabase(LoadDBPathFromFile());

    _mediationProcessVector = new MediationProcessVector();
    _mediationProcessView = nullptr;
    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);
    setCentralWidget(new LoginForm(this));

    // Listen for Events
    Mediator::Register(MKEY_GUI_ENABLE_MENUS, [this](MediatorArg arg){Q_UNUSED(arg);ShowMainMenu();});
    Mediator::Register(MKEY_GUI_DISABLE_MENUS, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuBarDisabled();SetMenuHelpDisabled();});
    Mediator::Register(MKEY_GUI_SHOW_ADMIN, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuAdminShow();});
    Mediator::Register(MKEY_GUI_HIDE_ADMIN, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuAdminHide();});
    Mediator::Register(MKEY_GUI_SHOW_MEDIATION_BROWSER, [this](MediatorArg arg){Q_UNUSED(arg);ShowMediationBrowser();});
    Mediator::Register(MKEY_GUI_SHOW_SESSIONS_BROWSER, [this](MediatorArg arg){Q_UNUSED(arg);ShowSessionBrowser();});
    Mediator::Register(MKEY_GUI_SHOW_NOTES_BROWSER, [this](MediatorArg arg){Q_UNUSED(arg);ShowNotesBrowser();});
    Mediator::Register(MKEY_GUI_MP_NEW_FORM, [this](MediatorArg arg){Q_UNUSED(arg);LoadMediationProcessView();});
    Mediator::Register(MKEY_GUI_SHOW_EVALUATION, [this](MediatorArg arg){Q_UNUSED(arg);ShowEvaluation();});
    Mediator::Register(MKEY_GUI_SHOW_MONTHLY_REPORT, [this](MediatorArg arg){Q_UNUSED(arg);ShowMonthlyReport();});
    Mediator::Register(MKEY_GUI_SHOW_RESWA_REPORT, [this](MediatorArg arg){Q_UNUSED(arg);ShowResWaReport();});



    // Toolbar manager setup
    ToolbarManager::Instance().SetToolbar(ui->toolBar);
    ToolbarManager::Instance().Clear();

    // Disable Menus Until Logged In
    SetMenusEnabled(false, false);
}

DRCClient::~DRCClient()
{
   delete ui;
}

void DRCClient::SetMenusEnabled(bool enableMenus, bool showAdmin)
{
    ui->menuBar->setEnabled(enableMenus);
    ui->toolBar->setEnabled(enableMenus);
    ui->menuAdmin->menuAction()->setVisible(showAdmin);
}

void DRCClient::SetMenuBarEnabled()
{
    ui->menuBar->setEnabled(true);
    ui->toolBar->setEnabled(true);
}

void DRCClient::SetMenuHelpEnabled()
{
//    ui->menuHelp->setEnabled(true);
}

void DRCClient::SetMenuBarDisabled()
{
    ui->menuBar->setEnabled(false);
}

void DRCClient::SetMenuHelpDisabled()
{
//    ui->menuHelp->setEnabled(false);
}

void DRCClient::SetMenuAdminShow()
{
    ui->menuAdmin->menuAction()->setVisible(true);
}

void DRCClient::SetMenuAdminHide()
{
    ui->menuAdmin->menuAction()->setVisible(false);
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

void DRCClient::on_actionLogout_User_triggered()
{
    ui->toolBar->clear();
    if(_browserDock && _browserDock->isVisible())
        _browserDock->close();
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
    if(_mediationProcessView)
    {
//        delete _mediationProcessView;
        _mediationProcessView = nullptr;
    }

    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this, process);
    else _mediationProcessView->SetMediationProcess(process);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::ShowNotesBrowser()
{
    ShowBrowser(MPBROWSER_NOTES);
}

void DRCClient::ShowSessionBrowser()
{
    ShowBrowser(MPBROWSER_SESSIONS);
}

void DRCClient::ShowMediationBrowser()
{
    ShowBrowser(MPBROWSER_MEDIATION);
}

void DRCClient::ShowBrowser(MPBrowserTypes browserType)
{
    // If the browser is open, and they selected the current type, close it.
    // Otherwise, show the type they selected.
    bool shouldDisplayTable = true;

    // If the browser dock already exists - check if we're closing it.
    if(_browserDock)
    {
        // Close the current window if the same browser is requested.
        MPToolBox* toolbox = (MPToolBox*)_browserDock->widget();
        MPBrowserTypes curBrowser = toolbox->GetCurrentBrowserType();
        if(curBrowser == browserType)
        {
            if(_browserDock->isVisible())
            {
                _browserDock->close();
                removeDockWidget(_browserDock);
                disconnect(toolbox, SIGNAL(MPSelected(MediationProcess*)), this, SLOT(on_mediationProcessSelected(MediationProcess*)));
                _browserDock = nullptr;
                shouldDisplayTable = false;
            }
            else
            {
                _browserDock->show();
                shouldDisplayTable = false;
            }
        }
    }

    if(shouldDisplayTable)
    {
        // Create a new one if it doesn't exist.
        MPToolBox* mpToolbox = nullptr;
        if(_browserDock)
        {
            mpToolbox = (MPToolBox*)_browserDock->widget();
        }
        else
        {
            _browserDock = new QDockWidget("Browser Toolbox", this);
            mpToolbox = new MPToolBox(_browserDock);
            connect(mpToolbox, SIGNAL(MPSelected(MediationProcess*)), this, SLOT(on_mediationProcessSelected(MediationProcess*)));
            _browserDock->setWidget(mpToolbox);
            addDockWidget(Qt::RightDockWidgetArea, _browserDock);
        }
        mpToolbox->ShowBrowser(browserType);

        // Update all the views, including the browsers
        if(_mediationProcessView)
            _mediationProcessView->PopulateView();

        _browserDock->show();
    }
}

void DRCClient::on_actionNew_2_triggered()
{
    _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(new MediationProcess());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::on_actionAdd_1_MP_sample_triggered()
{
    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(MediationProcess::SampleData());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::on_actionAdd_to_vector_triggered()
{
    _mediationProcessVector->push_back(_mediationProcessView->GetMediationProcess());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
}
// use to add mp via save event
void DRCClient::saveMPEvent(MediatorArg arg)
{
    MediationProcess* process = arg.getArg<MediationProcess*>();
    if(process)
    {
        _mediationProcessVector->push_back(process);
        Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    }
}

void DRCClient::on_actionSave_to_file_triggered()
{
//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::AnyFile);
//    dialog.setNameFilter(tr("*.mp"));
//    dialog.setViewMode(QFileDialog::Detail);

//    if(dialog.exec())
//        QStringList fileName = dialog.selectedFiles();
   if(_mediationProcessView)
   {
        QString Filter = "Mediation Processes (*.mp)";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                    "",
                                    Filter,&Filter);

        _filemaker.setFileName(fileName);
        _filemaker.sendToFile(_mediationProcessVector);
   }
}

void DRCClient::on_actionLoad_from_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("*.mp"));
    if(!fileName.isEmpty())
    {
        _filemaker.getFromFile(fileName);
        _mediationProcessVector = _filemaker.getMedationProcessVector();
        if(_mediationProcessView)
        {
            //delete _mediationProcessView;
            _mediationProcessView = nullptr;
        }
        _mediationProcessView = new MediationProcessView(this);
        _mediationProcessView->SetMediationProcess(_mediationProcessVector->at(0));
        Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
        setCentralWidget(_mediationProcessView);
    }

}

void DRCClient::on_actionAdd_5_MP_samples_triggered()
{
    for(int i = 0; i < 5; i++)
    {
        _mediationProcessVector->push_back(MediationProcess::SampleData());
    }
    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(_mediationProcessVector->at(0));
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}
void DRCClient::send_mediation_vector()
{
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
}

void DRCClient::on_actionManage_Users_triggered()
{
    setCentralWidget(new ManageUsers(this));
}

// Allow the admin to find a remote .db3 file to use. This file location will be stored as a file.
void DRCClient::on_actionConnect_to_Remote_DB_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Remote Database", "", "Db Files (*.db3)");

    if(fileName.length())
    {
        QFile file(DBPATH_FILE);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(fileName.toStdString().c_str());
            file.close();
            _db.LoadDatabase(fileName);
        }
    }

}

QString DRCClient::LoadDBPathFromFile()
{
    QString fileName = "";

    QFile file(DBPATH_FILE);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        fileName = in.readLine();
        file.close();
    }

    if(!fileName.length())
    {
        fileName = DB_DEFAULT_PATH;
    }
    return fileName;
}

void DRCClient::on_actionFindMediation_triggered()
{
    ShowMediationBrowser();
}

void DRCClient::ShowMainMenu()
{
    _mediationProcessView = nullptr;
    SetMenuBarEnabled();
    SetMenuHelpEnabled();
    ToolbarManager::Instance().Clear();
    setCentralWidget(new MainMenuForm(this));
}

void DRCClient::ShowEvaluation()
{

}

void DRCClient::ShowResWaReport()
{
    _mediationProcessView = nullptr;
    setCentralWidget(new ResWaReportForm(this));
}

void DRCClient::ShowMonthlyReport()
{

}
