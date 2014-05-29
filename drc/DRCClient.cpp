
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "bl/drcbl.h"
#include "db/drcdb.h"
#include <QDebug>
#include "gui/fruitnameform.h"

DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient),
   _fruitForm(new FruitNameForm())
{
   ui->setupUi(this);

   // Set the initial subview
   _fruitForm->setParent(ui->centralWidget);
   ui->centralWidget = _fruitForm;
}

DRCClient::~DRCClient()
{
   delete ui;
}





