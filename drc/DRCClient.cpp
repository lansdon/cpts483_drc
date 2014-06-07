
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
}

DRCClient::~DRCClient()
{
   delete ui;
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

void DRCClient::on_actionOpen_contact_view_triggered()
{
    setCentralWidget(new ContactRecordView());
}
