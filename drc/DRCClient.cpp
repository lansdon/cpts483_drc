
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "bl/drcbl.h"
#include "db/drcdb.h"

DRCClient::DRCClient(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::DRCClient)
{
   ui->setupUi(this);

   // Create the application components that will be listening for events.
   DRCBL bl;
   DRCDB db;

   asyncSendFruitName = new AsyncMediatorCall(MKEY_GUI_SEND_FRUIT_NAME, MKEY_BL_SEND_FRUIT_NAME_RESULT, [this](MediatorArg arg){ RecieveFruitNameResult(arg); }, new std::string("Kumquat"));
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
   UpdateNameField("Sending name: " + _name);
   //send info to logic to store into database
   SendFruitName(_name);
}

void DRCClient::UpdateNameField(QString str)
{
    ui->nameLabel->setText(str);
}

void DRCClient::on_nameLineEdit_returnPressed()
{
   on_sendButton_clicked();
}


//////////// SEND / RECIEVE EVENTS /////////////////

void DRCClient::SendFruitName(QString name)
{
    asyncSendFruitName->GetMediatorArg().SetArg( new std::string(name.toStdString()));
    asyncSendFruitName->Send();
}

void DRCClient::RecieveFruitNameResult(MediatorArg arg)
{
    bool success = true;
    std::string errorMessage;

    if (arg.IsSuccessful())
    {
        UpdateNameField("Fruit name successfully submitted.");
    }
    else
    {
        QString str = QString("Submit Name Error: ");
        str.append(QString::fromStdString(arg.ErrorMessage()));
        UpdateNameField(str);
    }
}
