#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"
#include <QWidget>
#include <QListWidget>
#include "mediationprocess.h"
#include "partiescontainerform.h"
#include "party.h"
#include <QToolBox>
#include "mediationprocessstatusform.h"
#include <QDebug>
#include "toolbarmanager.h"


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
    toolBox->addItem(new PartiesContainerForm(toolBox, &_mediationProcess->GetParties()), "Parties");

    _MediationSessionTabWidget = new QTabWidget();
    toolBox->addItem(new MediationSession(toolBox,_mediationProcess->getMediationSessionVector()),"Mediation Sessions");

    ui->gridLayout->addWidget(toolBox);

    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}


void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));

}

void MediationProcessView::SaveMediationPressed()
{
    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";
}

void MediationProcessView::SearchForMediationPressed()
{

}
