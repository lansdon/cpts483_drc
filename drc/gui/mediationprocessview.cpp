#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"
#include <QWidget>
#include <QListWidget>
#include "mediationprocess.h"
#include "partiescontainerform.h"
#include "party.h"
#include <QToolBox>
#include "mediationprocessstatusform.h"


MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    // TEMP SAMPLE DATA
    _mediationProcess = MediationProcess::SampleData();

    QToolBox* toolBox = new QToolBox(this);
    toolBox->addItem(new MediationProcessStatusForm(toolBox, _mediationProcess), "Mediation Overview");
    toolBox->addItem(new PartiesContainerForm(toolBox, _mediationProcess->GetParty1(), _mediationProcess->GetParty2()), "Parties");

    _MediationSessionTabWidget = new QTabWidget();
    toolBox->addItem(new MediationSession(toolBox),"Mediation Sessions");

    ui->gridLayout->addWidget(toolBox);

}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

//int MediationProcessView::getNumberOfParty()
//{
//    return _numberOfParties;
//}

//void MediationProcessView::on_toolBox_currentChanged(int index)
//{
//    if(index == 1)
//    {

//        //temp.insert(temp.begin(),_localIntakeForm->getCurrentIntake().getClaimant());

////        _numberOfParties = _localIntakeForm->totalParties();
//        //qDebug() << QString::fromStdString(std::to_string(temp.size()));
////        _localDetailsView->updateTabs(_localIntakeForm->getCurrentIntake().getParties());

//    }
//}
