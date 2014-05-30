
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "bl/drcbl.h"
#include "db/drcdb.h"
#include <QDebug>
#include "gui/fruitnameform.h"
#include "gui/mainmenutabwidget.h"


DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient)
{
   ui->setupUi(this);

   // Set the initial subview
 //  _fruitForm->setParent(ui->centralWidget);
   ui->centralWidget = new MainMenuTabWidget(this);
}

DRCClient::~DRCClient()
{
   delete ui;
}





