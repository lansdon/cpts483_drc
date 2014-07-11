#include "sessionsview.h"
#include "ui_sessionsview.h"

SessionsView::SessionsView(QWidget *parent, MediationSessionVector *vec) :
    QWidget(parent),
    ui(new Ui::SessionsView),
   _sessions(vec ? vec : new MediationSessionVector())
{
    ui->setupUi(this);
    populate();
}

SessionsView::~SessionsView()
{
    delete ui;
}

void SessionsView::populate()
{

    if(_sessions->size() > 0)
    {
        ui->NoSessionsLabel->setVisible(false);
        ui->sessionsTabWidget->setVisible(true);


        for(int i = 0; i < (int)_sessions->size(); i++)
        {
            ui->sessionsTabWidget->addTab(new MediationSessionForm(nullptr,_sessions->at(i)), _sessions->at(i)->getScheduledDate().toString("MM/dd/yyyy"));
        }
    }
    else
    {
        ui->sessionsTabWidget->setVisible(false);
        ui->NoSessionsLabel->setVisible(true);
    }
}

void SessionsView::on_addSessionPushButton_clicked()
{
    _sessions->push_back(new MediationSession());
    populate();
}

void SessionsView::on_sessionsTabWidget_tabCloseRequested(int index)
{
    _sessions->erase(_sessions->begin() + index);
    populate();
}
