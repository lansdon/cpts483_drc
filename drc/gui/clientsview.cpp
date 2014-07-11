#include "clientsview.h"
#include "ui_clientsview.h"
#include "party.h"

ClientsView::ClientsView(QWidget *parent, PartyVector *vec) :
    QWidget(parent),
    _partyVec(vec ? vec : new PartyVector()),
    ui(new Ui::ClientsView)
{
    ui->setupUi(this);
//    ui->ClientGroupBox->setStyleSheet("QGroupBox {\
//                                      border: 2px solid gray;\
//                                      border-radius: 5px;\
//                                      margin-top: 1.3em;\
//                                     } QGroupBox::title { subcontrol-origin: margin;\
//   subcontrol-position: top left;\
//   padding:0 3px;\
//}");
    populate();
}

ClientsView::~ClientsView()
{
    delete ui;
}

void ClientsView::populate()
{
    if(_partyVec->size() > 0)
    {
        ui->noClientsLabel->setVisible(false);
        ui->clientsTabWidget->setVisible(true);
        ui->clientsTabWidget->clear();
        for(int i = 0; i < (int)_partyVec->size(); i++)
        {
            ui->clientsTabWidget->addTab(new PersonDetailsForm(nullptr, _partyVec->at(i)->GetPrimary()),_partyVec->at(i)->GetPrimary()->FullName());
        }
    }
    else
    {
        ui->clientsTabWidget->setVisible(false);
        ui->noClientsLabel->setVisible(true);
    }
}

void ClientsView::on_pushButton_clicked()
{
    _partyVec->push_back(new Party());
    populate();
}

void ClientsView::on_clientsTabWidget_tabCloseRequested(int index)
{
    _partyVec->erase(_partyVec->begin() + index);
    populate();
}
