#include "sessioncell.h"
#include "ui_sessioncell.h"
#include "drctypes.h"

SessionCell::SessionCell(QWidget *parent, MediationSession* session) :
    QWidget(parent),
    ui(new Ui::SessionCell),
    _session(session)
{
    ui->setupUi(this);

    Populate();
}

SessionCell::~SessionCell()
{
    delete ui;
}

void SessionCell::Populate()
{
    if(_session)
    {
        ui->dateLabel->setText(_session->getMediationTime().toString("MM-dd-yyyy"));
        ui->statusLabel->setText(_session->getStatus());
        ui->paidLabel->setText("To do?");
    }
}
