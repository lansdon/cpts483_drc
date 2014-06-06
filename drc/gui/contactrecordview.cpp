#include "contactrecordview.h"
#include "ui_contactrecordview.h"
#include <QWidget>
#include <QListWidget>

ContactRecordView::ContactRecordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactRecordView)
{
    ui->setupUi(this);
    ui->toolBox->removeItem(0);
    _localIntakeForm = new IntakeForm();
    ui->toolBox->addItem(_localIntakeForm,"Contact Information");
    _MediationSessionTabWidget = new QTabWidget();
    _localMediationSession = new MediationSession();
    _numberOfParties = _localIntakeForm->totalParties();
   // _localMediationSession->setParties(_numberOfParties);
    _MediationSessionTabWidget->addTab(_localMediationSession,QString::fromStdString("Session " + std::to_string(_MediationSessionTabWidget->count() + 1)));
    ui->toolBox->addItem(_MediationSessionTabWidget, "Mediation Session");

}

ContactRecordView::~ContactRecordView()
{
    delete ui;
}

int ContactRecordView::getNumberOfParty()
{
    return _numberOfParties;
}

void ContactRecordView::on_toolBox_currentChanged(int index)
{
    if(index == 1)
    {

        //temp.insert(temp.begin(),_localIntakeForm->getCurrentIntake().getClaimant());

        _numberOfParties = _localIntakeForm->totalParties();
        //qDebug() << QString::fromStdString(std::to_string(temp.size()));
        _localMediationSession->updateTabs(_localIntakeForm->getCurrentIntake().getParties());

    }
}
