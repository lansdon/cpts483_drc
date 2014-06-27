#include "notesbrowser.h"
#include "ui_notesbrowser.h"
#include <QDateTime>
#include <QDebug>>
#include "Note.h"
#include "Mediator.h"
#include "MediatorKeys.h"

NotesBrowser::NotesBrowser(QWidget *parent, MediationNotesVector* notesVec)
    : QWidget(parent)
    , ui(new Ui::NotesBrowser)
    , _notes(notesVec)

{
    ui->setupUi(this);

    Mediator::Register(MKEY_DOCK_SET_NOTES, [this](MediatorArg arg){SetNotesEvent(arg);});

    ConfigTable();
    PopulateTable();
}

NotesBrowser::~NotesBrowser()
{
    delete ui;
}

void NotesBrowser::on_tableWidget_doubleClicked(const QModelIndex &index)
{

}

void NotesBrowser::ConfigTable()
{
    if(!_notes) _notes = new MediationNotesVector();

    //ui->tableWidget = ui->sessiontTableWidget;
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(_notes->size());
    QStringList header;
    header <<"Date"<<"Note";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");

    // only stretch note column
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        1, QHeaderView::Stretch);
}

void NotesBrowser::PopulateTable()
{
    ui->tableWidget->setRowCount(_notes->size());
    for(int row=0; row < (int)_notes->size(); ++row)
    {
        //insert data
        Note *note = _notes->at(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(note->GetCreatedDate().toString("MM-dd-yyyy")));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(note->GetMessage()));
    }
}

void NotesBrowser::SetNotes(MediationNotesVector* notes)
{
    _notes = notes;
    PopulateTable();
}

void NotesBrowser::SetNotesEvent(MediatorArg arg)
{
    MediationNotesVector* notes = arg.getArg<MediationNotesVector*>();
    if(notes)
    {
        SetNotes(notes);
    }
}

void NotesBrowser::on_saveNoteBtn_clicked()
{
    QString note = ui->noteInput->toPlainText();
    if(note.length())
    {
        _notes->push_back(new Note(note));
        ui->noteInput->clear();
        Mediator::Call(MKEY_GUI_MP_SHOULD_UPDATE);
    }
}
