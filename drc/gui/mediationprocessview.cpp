#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"
#include <QWidget>
#include <QListWidget>
#include "mediationprocess.h"
#include "partiescontainerform.h"
#include "party.h"


MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    // TEMP SAMPLE DATA
    _mediationProcess = MediationProcess::SampleData();

    ui->toolBox->removeItem(0);

    ui->toolBox->addItem(new PartiesContainerForm(this, _mediationProcess->GetParty1(), _mediationProcess->GetParty2()), "Parties");

    _MediationSessionTabWidget = new QTabWidget();
    ui->toolBox->addItem(new MediationSession(),"Mediation Sessions");

}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

//int MediationProcessView::getNumberOfParty()
//{
//    return _numberOfParties;
//}

void MediationProcessView::on_toolBox_currentChanged(int index)
{
    if(index == 1)
    {

        //temp.insert(temp.begin(),_localIntakeForm->getCurrentIntake().getClaimant());

//        _numberOfParties = _localIntakeForm->totalParties();
        //qDebug() << QString::fromStdString(std::to_string(temp.size()));
//        _localDetailsView->updateTabs(_localIntakeForm->getCurrentIntake().getParties());

    }
}
