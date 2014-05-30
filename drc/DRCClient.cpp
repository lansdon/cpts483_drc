
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "bl/drcbl.h"
#include "db/drcdb.h"
#include <QDebug>
#include "gui/fruitnameform.h"
#include "gui/mainmenutabwidget.h"
#include <QTimer>
#include <QGridLayout>
#include "gui/intakeform.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include "gui/intakeform.h"

DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient),
   _fruitForm(new FruitNameForm())
{
    ui->setupUi(this);

    // Set layout with Tab View with Tabs.
    QHBoxLayout *layout = new QHBoxLayout;
    QTabWidget* tw = new QTabWidget();
    tw->addTab(new FruitNameForm(), "Fruit Name");
    tw->addTab(new IntakeForm(), "Intake Form");
    layout->addWidget(tw);

    // Add layout to QWidget (The main frame holding all our subviews.)
    QWidget *window = new QWidget();
    window->setLayout(layout);

    // Set QWidget as the central layout of the main window
    setCentralWidget(window);

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



