#include "sessionstableform.h"
#include "ui_sessionstableform.h"
#include "mediationsessionform.h"

SessionsTableForm::SessionsTableForm(QWidget *parent, MediationSessionVector* sessions) :
    QWidget(parent),
    ui(new Ui::SessionsTableForm),
    _sessions(sessions ? sessions : new MediationSessionVector)
{
    ui->setupUi(this);

    configSessionTable();
}

SessionsTableForm::~SessionsTableForm()
{
    delete ui;
}


void SessionsTableForm::configSessionTable()
{
    _sessionTable = ui->tableWidget;
    _sessionTable->setColumnCount(1);
    _sessionTable->setRowCount(_sessions->size() + 1);
//    QStringList _sessionTableHeader <<"Mediation Sessions";
    _sessionTable->setHorizontalHeaderLabels({"Mediation Sessions"});
    _sessionTable->verticalHeader()->setVisible(false);
    _sessionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _sessionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _sessionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _sessionTable->setShowGrid(true);
    _sessionTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _sessionTable->horizontalHeader()->count(); ++c)
    {
        _sessionTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void SessionsTableForm::PopulateSessionTable()
{
    _sessionTable->clearContents();

//    MediationSessionVector* sessionsVec = _mediationProcess->getMediationSessionVector();
    int row;
    for(row=0; row < (int)_sessions->size(); ++row)
    {
        MediationSessionForm* sessionForm = new MediationSessionForm(_sessionTable, _sessions->at(row));
        _sessionTable->insertRow(row);
        _sessionTable->setRowHeight(row, 100);
        _sessionTable->setCellWidget(row, 0, sessionForm);
 //       _sessionTable->setItem(row, 0, new MediationSessionForm(_sessionTable, session));
    }
    _sessionTable->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    _sessionTable->setCurrentCell(0,0);
}

void SessionsTableForm::on_sessiontTableWidget_itemSelectionChanged()
{

//    if(sessionCurrentRow != ui->sessiontTableWidget->currentRow())
//    {
//        sessionCurrentRow = ui->sessiontTableWidget->currentRow();

//        if((uint)sessionCurrentRow<_mediationSessions->size())
//            fillFields(_mediationSessions->at(sessionCurrentRow));
//    }

}
