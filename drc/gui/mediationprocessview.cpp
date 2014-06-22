#include "mediationprocessview.h"
#include "ui_mediationprocessview.h"

// QT
#include <QWidget>
#include <QListWidget>
#include <QToolBox>
#include <QDebug>

// DRC
#include "mediationprocessstatusform.h"
#include "toolbarmanager.h"
#include "DRCModels.h"
#include "partiescontainerform.h"
#include "MediatorKeys.h"




MediationProcessView::MediationProcessView(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessView),
    _mediationProcess(mediationProcess ? mediationProcess : new MediationProcess)
{
    ui->setupUi(this);

    _mediationProcessStatusForm = new MediationProcessStatusForm(ui->overviewContainer, _mediationProcess);
    _partiesContainerForm = new PartiesContainerForm(this, &_mediationProcess->GetParties());
    _mediationSessionForm = new MediationSessionForm(this);

    // Set the overview container
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mediationProcessStatusForm);
    ui->overviewContainer->setLayout(layout);
//    connect(_mediationProcessStatusForm,SIGNAL(hovered()),this, SLOT(onHovered()));

    // Set the overview container
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(_partiesContainerForm);
    ui->clientsContainer->setLayout(pLayout);

    // Set the overview container
    QVBoxLayout* sLayout = new QVBoxLayout();
    sLayout->addWidget(_mediationSessionForm);
    ui->sessionsContainer->setLayout(sLayout);

    ConfigureToolbox();

    // Update Fields for current record
    PopulateView(_mediationProcess);

    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}

void MediationProcessView::ConfigureToolbox()
{
//    _toolBox = ui->MediationProcessToolBox;
//    ui->MediationProcessToolBox->removeItem(0);
//    //_toolBox->addItem(_mediationProcessStatusForm, "Mediation Overview");
//    _toolBox->addItem(_partiesContainerForm, "Parties");
//    _toolBox->addItem(_mediationSessionForm,"Mediation Sessions");

//    foreach(QWidget* child, _toolBox->findChildren<QWidget*>())
//        if( child->inherits("QToolBoxButton") )
//            child->setFont(QFont("Helvetica", 28, 5));
}

void MediationProcessView::savePersonContactFromFarAway(Person *value)
{
    PopulateView(_mediationProcess);
}

void MediationProcessView::PopulateView(MediationProcess *process)
{
    _mediationProcess = process;
    if(!_mediationProcess)
        _mediationProcess = new MediationProcess();

    _mediationProcessStatusForm->setMediationProcess(_mediationProcess);
    _mediationSessionForm->setMediationSessionVector(_mediationProcess->getMediationSessionVector());
    _partiesContainerForm->AddPartyTabs(&_mediationProcess->GetParties());
    connect(_partiesContainerForm,SIGNAL(PassItOnAgain(Person*)),this,SLOT(savePersonContactFromFarAway(Person*)));
}

void MediationProcessView::ConfigureToolbar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Mediation Record", this, SLOT(SaveMediationPressed()));
    toolbar.AddAction("Search for Mediation", this, SLOT(SearchForMediationPressed()));
    toolbar.AddAction("Show Recent Records", this, SLOT(ShowRecentPressed()));
}

void MediationProcessView::SaveMediationPressed()
{
    qDebug() << "SAVE MEDIATION PRESSED - Toolbar manager.";

}

void MediationProcessView::SearchForMediationPressed()
{
    qDebug() << "SEARCH MEDIATION PRESSED - Toolbar manager.";
}



void MediationProcessView::ShowRecentPressed()
{
    Mediator::Call(MKEY_GUI_TOGGLE_MEDIATION_TABLE_DOCK);
}

void MediationProcessView::SetMediationProcess(MediationProcess* process)
{
    _mediationProcess = process;
    PopulateView(_mediationProcess);
}
