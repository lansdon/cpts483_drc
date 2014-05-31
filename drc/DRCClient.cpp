
#include "DRCClient.h"
#include "ui_DRCClient.h"


// GUI STUFF
#include <QGridLayout>
#include <QTabWidget>
#include "gui/intakeform.h"
#include "gui/fruitnameform.h"
#include "gui/intakeform.h"

// DRC COMPONENTS
#include "bl/drcbl.h"
#include "db/drcdb.h"

// MISC
#include <QDebug>

DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient)
{
    ui->setupUi(this);



    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);
}

DRCClient::~DRCClient()
{
   delete ui;
}

void DRCClient::showFullScreen()
{
//    QMainWindow::showFullScreen();
}



void DRCClient::on_actionNew_Fruit_Submission_triggered()
{
    setCentralWidget(new FruitNameForm(this));
}

void DRCClient::on_actionNew_Form_triggered()
{
    setCentralWidget(new IntakeForm(this));
}
