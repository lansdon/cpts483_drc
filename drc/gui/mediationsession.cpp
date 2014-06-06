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
    ui->tabWidget_2->clear();
    _attorneyAndSupportVector.clear();
    for(int i = 0; i < input;i++)
    {
        _attorneyAndSupportVector.push_back(new AttorneyAndSupportForMediationSessionView());
        ui->tabWidget_2->addTab(_attorneyAndSupportVector.at(i),QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));

    }
}

void MediationSession::updateTabs(std::vector<Person *> input)
{
//    AttorneyAndSupportForMediationSessionView *_attorneyAndSupport;
//    ui->tabWidget_2->clear();
//    for(uint i = 0; i < input.size();i++)
//    {
//        _attorneyAndSupport = new AttorneyAndSupportForMediationSessionView();
//        _attorneyAndSupport->setAttorney(QString::fromStdString(input[i].getAttorney()));
//            qDebug() << QString::fromStdString(input[i].getAttorney());

//            ui->tabWidget_2->addTab(_attorneyAndSupport, QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));


//    }
//    ui->tabWidget_2->repaint();


        //input -= ui->tabWidget_2->count();
        qDebug() << "tab widget size " << ui->tabWidget_2->count();
        if(input.size() > ui->tabWidget_2->count())
        {
            for(uint i = (ui->tabWidget_2->count()); i < input.size(); i++)
            {
                qDebug() << i;
                _attorneyAndSupportVector.push_back(new AttorneyAndSupportForMediationSessionView());
                ui->tabWidget_2->addTab(_attorneyAndSupportVector.at(i),QString::fromStdString("Party " + std::to_string(ui->tabWidget_2->count() + 1)));
            }
        }
        else
        {
            for(int i = input.size();i < ui->tabWidget_2->count(); i++)
                ui->tabWidget_2->removeTab(ui->tabWidget_2->count()-1);
        }

    qDebug() << "input size: " << input.size();
    qDebug() << "attorney Vector size: " << _attorneyAndSupportVector.size();
    if(input.size() == _attorneyAndSupportVector.size())
    {
        for(uint i = 0; i < _attorneyAndSupportVector.size(); i++)
        {
            qDebug() << i;
            qDebug() << QString::fromStdString(input.at(i)->getAttorney());
            _attorneyAndSupportVector.at(i)->setAttorney(QString::fromStdString(input.at(i)->getAttorney()));
        }
    }
}
