#include "fruitnameform.h"
#include "ui_fruitnameform.h"
#include <QDebug>
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
//#include "drc_shared/models/DRCModels.h"

FruitNameForm::FruitNameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FruitNameForm)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(new Particapants(),"tab 1");

    ui->widget = new Particapants(ui->widget);
    // One time setup of async handler.
    asyncSendFruitName = new AsyncMediatorCall(MKEY_GUI_SUBMIT_FRUIT_NAME, MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){ RecieveFruitNameResult(arg); }, new std::string("Kumquat"), true);
    asyncSendSearch = new AsyncMediatorCall(MKEY_GUI_SEARCH_FOR_USERNAME, MKEY_BL_RETURN_SEARCH_RESULTS, [this](MediatorArg arg){UpdateForm(arg);}, new Intake(),true);
}

FruitNameForm::~FruitNameForm()
{
    delete ui;
}

void FruitNameForm::on_retrieveButton_clicked()
{
   //send request to logic to retrieve names from database based on date
    SendSearchName("search");
}

void FruitNameForm::on_sendButton_clicked()
{
    //// Filling out Intake form  ////
   Intake temp;
   Particapants *tempClaim = (Particapants*)ui->widget;
   temp.addClaimant(tempClaim->getName());
   for(int i = 0; i < ui->tabWidget->count();i++)
   {
       Particapants *tempRespond = (Particapants*)ui->tabWidget->widget(i);
       temp.addRespondents(tempRespond->getName());
   }




   UpdateNameField("Sending name: " + tempClaim->getName());
   //send info to logic to store into database
   SendFruitName(tempClaim->getName());
}
void FruitNameForm::UpdateForm(MediatorArg arg)
{
   Intake *recieved = arg.getArg<Intake*>();
//    Particapants *tempClaim = new Particapants(this);
 //   tempClaim->setName(recieved->getClaimant().getName());
//    ui->widget = tempClaim;
    qDebug() << QString::fromStdString(recieved->getClaimant().getName());
    qDebug() << QString::fromStdString(recieved->getRespondents()[0].getName());
    std::vector<Person> tempVec = recieved->getRespondents();
    ui->tabWidget->clear();
    Particapants *tempRespon;
   // tempClaim = new Particapants();
    for(uint i = 0; i < tempVec.size(); i++)
   {
        tempRespon = new Particapants();
        tempRespon->setName(tempVec[i].getName());
        ui->tabWidget->addTab(tempRespon, QString::fromStdString("tab " + std::to_string(ui->tabWidget->count()+1)));
    }
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

void FruitNameForm::SendSearchName(QString name)
{
    asyncSendSearch->GetMediatorArg().SetArg(new std::string(name.toStdString()));
    asyncSendSearch->Send();
}


void FruitNameForm::on_AddParty_clicked()
{

    ui->tabWidget->addTab(new Particapants(), QString::fromStdString("tab " + std::to_string(ui->tabWidget->count()+1)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void FruitNameForm::on_removePushButton_clicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

