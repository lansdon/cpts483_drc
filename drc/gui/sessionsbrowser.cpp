#include "sessionsbrowser.h"
#include "ui_sessionsbrowser.h"
#include "mediationsessionform.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "QDebug"
#include "sessioncell.h"

SessionsBrowser::SessionsBrowser(QWidget *parent, MediationSessionVector* sessions) :
    QWidget(parent),
    ui(new Ui::SessionsBrowser),
    _sessions(sessions ? sessions : new MediationSessionVector)
{
    ui->setupUi(this);

    configSessionTable();

    Mediator::Register(MKEY_DOCK_SET_SESSIONS, [this](MediatorArg arg){SetSessionsEvent(arg); });
}

SessionsBrowser::~SessionsBrowser()
{
    Mediator::Unregister(MKEY_DOCK_SET_SESSIONS, _setSessionsCallback);
    delete ui;
}


void SessionsBrowser::configSessionTable()
{
    _sessionTable = ui->tableWidget;
    _sessionTable->setColumnCount(1);
    _sessionTable->setRowCount(10);
//    QStringList _sessionTableHeader <<"Mediation Sessions";
    _sessionTable->setHorizontalHeaderLabels({"Mediation Sessions"});
    _sessionTable->verticalHeader()->setVisible(false);
    _sessionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _sessionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _sessionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _sessionTable->setShowGrid(true);
    _sessionTable->setStyleSheet("QTableView {selection-background-color: red;}");

    connect(
      _sessionTable->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(on_tableWidget_itemSelectionChanged())
     );

    for (int c = 0; c < _sessionTable->horizontalHeader()->count(); ++c)
    {
        _sessionTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void SessionsBrowser::PopulateSessionTable()
{
    if(_sessions->size())
    {
        ui->noSessionLabel1->setVisible(false);
        ui->noSessionLabel2->setVisible(false);

        _sessionTable->setVisible(true);
        _sessionTable->clearContents();
        _sessionTable->setRowCount(_sessions->size());
        _sessionTable->setStyleSheet("QTableView {selection-background-color: red;}");

        int row;
        for(row=0; row < (int)_sessions->size(); ++row)
        {
            SessionCell* sessionForm = new SessionCell(_sessionTable, _sessions->at(row));
//            _sessionTable->insertRow(row);
            _sessionTable->setCellWidget(row, 0, sessionForm);
            _sessionTable->setRowHeight(row, 50);
        }
 //       _sessionTable->insertRow(row);
 //       _sessionTable->setItem(row, 0, new QTableWidgetItem("Double click here to add a new session->"));
    }
    else    // NO SESSIONS
    {
        _sessionTable->setVisible(false);
        ui->noSessionLabel1->setVisible(true);
        ui->noSessionLabel2->setVisible(true);
    }
}

void SessionsBrowser::on_tableWidget_itemSelectionChanged()
{
    qDebug() << "Look ma! Session changed!";

    if(_sessionTable->rowCount() <= 1) return;

    SessionCell* sessionForm = (SessionCell*)_sessionTable->cellWidget(_sessionTable->currentRow(), 0);
    if(sessionForm)
    {
       MediationSession* session = sessionForm->GetSession();
       if(session && _sessions->size() >= 1)
       {
           Mediator::Call(MKEY_DOCK_SESSION_CHANGED, sessionForm->GetSession());
       }
    }
}

void SessionsBrowser::SetSessions(MediationSessionVector* sessions)
{
    _sessions = sessions ? sessions : new MediationSessionVector;
    PopulateSessionTable();
}

void SessionsBrowser::SetSessionsEvent(MediatorArg arg)
{
    SetSessions(arg.getArg<MediationSessionVector*>());
}

void SessionsBrowser::on_addSessionBtn_clicked()
{
    if(_sessions)
    {
        MediationSession* session = new MediationSession;
        _sessions->push_back(session);
        int row = _sessions->size()-1;
        _sessionTable->insertRow(row);
        _sessionTable->setCellWidget(row, 0, new SessionCell(_sessionTable, _sessions->back()));
        _sessionTable->setRowHeight(row, 50);
        PopulateSessionTable();
//        Mediator::Call(MKEY_GUI_MP_POPULATE);
        Mediator::Call(MKEY_DOCK_SESSION_CHANGED, session);

    }
}

void SessionsBrowser::on_delSessionBtn_clicked()
{
    if((int)_sessions->size() > _sessionTable->currentIndex().row())
    {
        _sessions->erase(_sessions->begin() + _sessionTable->currentIndex().row());
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
}
