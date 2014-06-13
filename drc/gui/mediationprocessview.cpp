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
    _localMediationProcessVector = new MediationProcessVector();
    // TEMP SAMPLE DATA
    for(int i = 0; i < 7; i++)
        _localMediationProcessVector->push_back(MediationProcess::SampleData());



//    QToolBox* toolBox = new QToolBox(this);
//    toolBox->addItem(new MediationProcessStatusForm(toolBox, _mediationProcess), "Mediation Overview");
//    toolBox->addItem(new PartiesContainerForm(toolBox, &_mediationProcess->GetParties()), "Parties");


    //_mediationProcess = MediationProcess::SampleData();



    MediationProcessTableView = ui->MediationProcessTableWidget;
    MediationProcessTableView->setMaximumHeight(200);
    configMediationProcecssViewTable();
    PopulateMediationProcessTable();
    toolBox = ui->MediationProcessToolBox;
    _localMediationProcessStatusForm = new MediationProcessStatusForm();
    _localPartiesContainerForm = new PartiesContainerForm();
    _localMediationSession = new MediationSession();
    ui->MediationProcessToolBox->removeItem(0);
    //ui->verticalLayout->addWidget(MediationProcessTableView);
    //ui->verticalLayout->addWidget(toolBox);
    MediationProcessCurrentRow= 1;
    toolBox->addItem(_localMediationProcessStatusForm, "Mediation Overview");
    toolBox->addItem(_localPartiesContainerForm, "Parties");
    toolBox->addItem(_localMediationSession,"Mediation Sessions");
   PopulateView(_localMediationProcessVector->at(MediationProcessCurrentRow));

    ConfigureToolbar();
}

MediationProcessView::~MediationProcessView()
{
    delete ui;
}
void MediationProcessView::PopulateView(MediationProcess *value)
{
    _localMediationProcessStatusForm->setMediationProcess(value);
//    _localPartiesContainerForm->SetParty1View(value->GetParty1());
//    _localPartiesContainerForm->SetParty2View(value->GetParty2());
    _localMediationSession->setMediationSessionClassVector(value->getMediationSessionVector());
    //_localMediationProcessStatusForm->repaint();
   // _localPartiesContainerForm->repaint();
   // _localMediationSession->repaint();
}

void MediationProcessView::configMediationProcecssViewTable()
{

        //MediationProcessTableView = ui->sessiontTableWidget;
        MediationProcessTableView->setColumnCount(3);
        MediationProcessTableView->setRowCount(11);
        MediationProcessTableViewHeader <<"Date Time"<<" "<<"Status";
        MediationProcessTableView->setHorizontalHeaderLabels(MediationProcessTableViewHeader);
        MediationProcessTableView->verticalHeader()->setVisible(false);
        MediationProcessTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        MediationProcessTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        MediationProcessTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        MediationProcessTableView->setShowGrid(true);
        MediationProcessTableView->setStyleSheet("QTableView {selection-background-color: red;}");

        for (int c = 0; c < MediationProcessTableView->horizontalHeader()->count(); ++c)
        {
            MediationProcessTableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }

}
void MediationProcessView::PopulateMediationProcessTable()
{
    int row=0;
     MediationProcessTableView->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    for(row=1; row < (int)_localMediationProcessVector->size()+1; ++row)
    {
        //insert data
        MediationProcess *o = _localMediationProcessVector->at(row-1);

        MediationProcessTableView->setItem(row, 0, new QTableWidgetItem(o->GetCreationDate().toString()));


        MediationProcessTableView->setItem(row, 2, new QTableWidgetItem(o->GetCurrentState()));

    }

    //ui->sessiontTableWidget->setCurrentCell(0,0);
}
//int MediationProcessView::getNumberOfParty()
//{
//    return _numberOfParties;
//}


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


//    }
//}



void MediationProcessView::on_MediationProcessTableWidget_itemSelectionChanged()
{
    if(MediationProcessCurrentRow != ui->MediationProcessTableWidget->currentRow())
    {
        MediationProcessCurrentRow = ui->MediationProcessTableWidget->currentRow();

        if((uint)MediationProcessCurrentRow < _localMediationProcessVector->size())
            PopulateView(_localMediationProcessVector->at(MediationProcessCurrentRow));
    }
}
void MediationProcessView::SearchForMediationPressed()
{


}
