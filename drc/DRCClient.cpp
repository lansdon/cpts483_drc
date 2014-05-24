#include "DRCClient.h"
#include "ui_DRCClient.h"

DRCClient::DRCClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DRCClient)
{
    ui->setupUi(this);
}

DRCClient::~DRCClient()
{
    delete ui;
}
