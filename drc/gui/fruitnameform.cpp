#include "fruitnameform.h"
#include "ui_fruitnameform.h"

// Qt
#include <QDebug>
#include <QWidget>

// DRC
#include "Mediator.h"
#include "AsyncMediatorCall.h"
#include "DRCModels.h"
#include "persondetailsform.h"


FruitNameForm::FruitNameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FruitNameForm)
{
    ui->setupUi(this);

    ui->tabWidget->clear();
    ui->tabWidget->addTab(new PartyDetailsForm(),"tab 1");
    ui->claimentTabWidget->clear();
    ui->claimentTabWidget->addTab((claiment=new PartyDetailsForm(ui->claimentTabWidget)), QString::fromStdString("Claiment " + std::to_string(ui->claimentTabWidget->count() + 1)));

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
   //Particapants *tempClaim = (Particapants*)ui->widget;
   temp.addClaimant(*claiment->GetPerson());
   for(int i = 0; i < ui->tabWidget->count();i++)
   {
       PartyDetailsForm *tempRespond = (PartyDetailsForm*)ui->tabWidget->widget(i);
       temp.addRespondents(*tempRespond->GetPerson());
   }

   UpdateNameField("Sending name: " + QString::fromStdString(claiment->GetPerson()->getFirstName()));
   //send info to logic to store into database
   SendFruitName(new Fruit(claiment->GetPerson()->getFirstName()));
}
void FruitNameForm::UpdateForm(MediatorArg arg)
{
    qDebug() << "GUI -> UpdateForm Callback...";
    if(arg.IsSuccessful())
    {
        Intake *recieved = arg.getArg<Intake*>();

        //ui->widget->setName();
        if(recieved)
        {
            //claiment->SetPerson(recieved->getClaimant());
            //claiment->repaint();
            qDebug() << QString::fromStdString(recieved->getClaimant().getFirstName());
            //qDebug() << QString::fromStdString(recieved->getParties()[0].getFirstName());
            std::vector<Person *> tempVec = recieved->getParties();
            ui->tabWidget->clear();
            PartyDetailsForm* tempRespon;
            for(uint i = 0; i < tempVec.size(); i++)
           {
                tempRespon = new PartyDetailsForm();
                tempRespon->SetPerson(tempVec[i]);
                ui->tabWidget->addTab(tempRespon, QString::fromStdString("tab " + std::to_string(ui->tabWidget->count()+1)));
            }
        }
        else
        {
            qDebug() << "GUI -> INTAKE ARGUMENT ERROR";
            qDebug() << QString::fromStdString(arg.ErrorMessage());
        }
    }
    else
    {
        qDebug() << "RESPONSE NOT SUCCESSFUL!";
        qDebug() << QString::fromStdString(arg.ErrorMessage());
    }
}

void FruitNameForm::UpdateNameField(QString str)
{
    ui->nameLabel->setText(str);

}

//////////// SEND / RECIEVE EVENTS /////////////////

void FruitNameForm::SendFruitName(Fruit *fruit)
{
    qDebug() << "Gui -> Submit fruit name asynchronously" << QString::fromStdString(fruit->GetName());
    qDebug() <<  QString::fromStdString(fruit->GetName());
    asyncSendFruitName->GetMediatorArg().SetArg((Fruit*)fruit);
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

    ui->tabWidget->addTab(new PartyDetailsForm(), QString::fromStdString("tab " + std::to_string(ui->tabWidget->count()+1)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void FruitNameForm::on_removePushButton_clicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

