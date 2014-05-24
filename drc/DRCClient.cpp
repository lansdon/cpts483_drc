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

void DRCClient::on_retrieveButton_clicked()
{
    //send request to logic to retrieve names from database based on date
}

void DRCClient::on_sendButton_clicked()
{
    IntakeForm temp;
    _name = ui->nameLineEdit->text();
    temp.addPerson(_name);
    ui->nameLabel->setText(_name);
    //send info to logic to store into database
}

void DRCClient::on_nameLineEdit_returnPressed()
{
    on_sendButton_clicked();
}
