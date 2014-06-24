#include "sessionoverview.h"
#include "ui_sessionoverview.h"

SessionOverview::SessionOverview(QWidget *parent, MediationSession *mediationSession) :
    QWidget(parent),
    _mediationSession(mediationSession ? mediationSession : new MediationSession()),
    ui(new Ui::SessionOverview)
{
    ui->setupUi(this);
    updateView();
}

SessionOverview::~SessionOverview()
{
    delete ui;
}

void SessionOverview::updateView()
{
    ui->sessionDateDisplayLabel->setText(_mediationSession->getMediationTime().toString());
    ui->sessionFeeStatusDisplayLabel->setText(_mediationSession->getFeeStatus());
    ui->sessionStatusDisplayLabel->setText(_mediationSession->getStatus());
}
