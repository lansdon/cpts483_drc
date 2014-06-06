#include "mediationsession.h"
#include "ui_mediationsession.h"
#include <QDebug>

MediationSession::MediationSession(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationSession)
{
    ui->setupUi(this);


}

MediationSession::~MediationSession()
{
    delete ui;
}
void MediationSession::setParties(int input)
{

    for(int i = 0; i < input;i++)
    {

        ui->tabWidget_2->addTab(new AttorneyAndSupportForMediationSessionView(),QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));
    }
}

void MediationSession::updateTabs(std::vector<Person> input)
{
    AttorneyAndSupportForMediationSessionView *_attorneyAndSupport;
    ui->tabWidget_2->clear();
    for(uint i = 0; i < input.size();i++)
    {
        _attorneyAndSupport = new AttorneyAndSupportForMediationSessionView();
        _attorneyAndSupport->setAttorney(QString::fromStdString(input[i].getAttorney()));
            qDebug() << QString::fromStdString(input[i].getAttorney());

            ui->tabWidget_2->addTab(_attorneyAndSupport, QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));


    }
    //ui->tabWidget_2->repaint();
//    if(input != ui->tabWidget_2->count())
//    {
//        input -= ui->tabWidget_2->count();
//        if(input > 0)
//        {
//            for(int i = 0; i < input; i++)
//                ui->tabWidget_2->addTab(new AttorneyAndSupportForMediationSessionView(),QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));
//        }
//        else
//        {
//            for(int i = input;i < 0; i++)
//                ui->tabWidget_2->removeTab(ui->tabWidget_2->count()-1);
//        }
//    }
}
