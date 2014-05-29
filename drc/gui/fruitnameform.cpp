#include "fruitnameform.h"
#include "ui_fruitnameform.h"
#include <QDebug>
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/models/DRCModels.h"

FruitNameForm::FruitNameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FruitNameForm)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(new Particapants(),"tab 1");

    // One time setup of async handler.
    asyncSendFruitName = new AsyncMediatorCall(MKEY_GUI_SUBMIT_FRUIT_NAME, MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){ RecieveFruitNameResult(arg); }, new std::string("Kumquat"), true);
}

FruitNameForm::~FruitNameForm()
{
    delete ui;
}

void FruitNameForm::on_retrieveButton_clicked()
{
   //send request to logic to retrieve names from database based on date
}

void FruitNameForm::on_sendButton_clicked()
{
   Intake temp;
   _name = ui->nameLineEdit->text();
   temp.addPerson(_name);
   UpdateNameField("Sending name: " + _name);
   //send info to logic to store into database
   SendFruitName(_name);
}

void FruitNameForm::UpdateNameField(QString str)
{
    ui->nameLabel->setText(str);
}

void FruitNameForm::on_nameLineEdit_returnPressed()
{
   on_sendButton_clicked();
}


//////////// SEND / RECIEVE EVENTS /////////////////

void FruitNameForm::SendFruitName(QString name)
{
    qDebug() << "Gui -> Submit fruit name asynchronously";
    asyncSendFruitName->GetMediatorArg().SetArg( new std::string(name.toStdString()));
    asyncSendFruitName->Send();
}

void FruitNameForm::RecieveFruitNameResult(MediatorArg arg)
{
    qDebug() << "Gui -> Recieve response - sumbit fruit name";

    if (arg.IsSuccessful())
    {
        UpdateNameField("Fruit name successfully submitted.");
    }
    else
    {
        QString error = QString("Submit Name Error: ");
        error.append(QString::fromStdString(arg.ErrorMessage()));
        UpdateNameField(error);
    }
}

void FruitNameForm::on_AddParty_clicked()
{

    ui->tabWidget->addTab(new Particapants(), QString::fromStdString("tab " + std::to_string(ui->tabWidget->count()+1)));
}
