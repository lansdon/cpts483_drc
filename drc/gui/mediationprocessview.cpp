#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"
#include <QWidget>
#include <QListWidget>

MediationProcessView::MediationProcessView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationProcessView)
{
    ui->setupUi(this);
    ui->toolBox->removeItem(0);
    _localIntakeForm = new IntakeForm();
    _MediationSessionTabWidget = new QTabWidget();
    _localMediationSession = new MediationSession();
    _localDetailsView = new DetailsView();
    ui->toolBox->addItem(_localIntakeForm,"Contact Information");


    _numberOfParties = _localIntakeForm->totalParties();
   // _localMediationSession->setParties(_numberOfParties);
    //_MediationSessionTabWidget->addTab(_localMediationSession,QString::fromStdString("Session " + std::to_string(_MediationSessionTabWidget->count() + 1)));
    ui->toolBox->addItem(_localDetailsView, "Details");

}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

int MediationProcessView::getNumberOfParty()
{
    return _numberOfParties;
}

void MediationProcessView::on_toolBox_currentChanged(int index)
{
    if(index == 1)
    {

        //temp.insert(temp.begin(),_localIntakeForm->getCurrentIntake().getClaimant());

        _numberOfParties = _localIntakeForm->totalParties();
        //qDebug() << QString::fromStdString(std::to_string(temp.size()));
        _localDetailsView->updateTabs(_localIntakeForm->getCurrentIntake().getParties());

    }
}
