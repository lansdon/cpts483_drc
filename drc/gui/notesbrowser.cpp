#include "notesbrowser.h"
#include "ui_notesbrowser.h"
#include <QDateTime>
#include <QDebug>>
#include "Note.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include <QMessageBox>
#include <iostream>

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
    qDebug() << "ConfigTable1";
    if(!_notes) _notes = new MediationNotesVector();
    qDebug() << "ConfigTable2";

    ui->tableWidget->setColumnCount(2);
    qDebug() << "ConfigTable2.5";
    ui->tableWidget->setRowCount(0);
    qDebug() << "ConfigTable3";
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
    qDebug() << "ConfigTable4";
}

void NotesBrowser::PopulateTable()
{
    try
    {
        qDebug() << "PopulateTable1";
        ui->tableWidget->setRowCount(_notes->size());
        qDebug() << "PopulateTable2";
        for(int row=0; row < (int)_notes->size(); ++row)
        {
            qDebug() << "PopulateTable" << row << "-1";
            //insert data
            Note *note = _notes->at(row);
            qDebug() << "SetNotes1" << row << "-2";
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(note->GetCreatedDate().toString("MM-dd-yyyy")));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(note->GetMessage()));
        }
    }
    catch(const std::exception& error)
    {
        QMessageBox msgBox;
        msgBox.setText( "BAM! Notes browser crashed: " + QString(error.what()));
        msgBox.show();
    }
    catch(...)
    {
        qDebug() << "There is an error.";
    }
}

void NotesBrowser::SetNotes(MediationNotesVector* notes)
{
    qDebug() << "SetNotes1";
    _notes = notes;
    qDebug() << "SetNotes2";
    ConfigTable();
    qDebug() << "SetNotes3";
    PopulateTable();
}

void NotesBrowser::SetNotesEvent(MediatorArg arg)
{
    qDebug() << "SetNotesEvent1";
    MediationNotesVector* notes = arg.getArg<MediationNotesVector*>();
    if(notes)
    {
        qDebug() << "SetNotesEvent2";
        SetNotes(notes);
    }
    else qDebug() << "SetNotesEvent failbot! ";
}

void NotesBrowser::on_saveNoteBtn_clicked()
{
    QString message = ui->noteInput->toPlainText();
    if(message.length())
    {
        // update the current note
        if(ui->tableWidget->currentRow() > ui->tableWidget->currentRow() && !_editingNewNote)
        {
            _notes->at(ui->tableWidget->currentRow())->SetMessage(message);
        }
        // Add a new note
        else _notes->push_back(new Note(message));
        ui->noteInput->clear();
        PopulateTable();
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
}

void NotesBrowser::on_delNoteBtn_clicked()
{
    if((_notes->size()) > ui->tableWidget->currentIndex().row())
    {
        if(_notes->size() != 1)
            _notes->erase(_notes->begin() + ui->tableWidget->currentIndex().row());
        else
            _notes = new MediationNotesVector();
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
}

void NotesBrowser::on_tableWidget_itemSelectionChanged()
{
    if(_notes->size() >= ui->tableWidget->currentRow())
    {
        Note* curNote = _notes->at(ui->tableWidget->currentRow());
        ui->noteInput->setText(curNote->GetMessage());
    }
    _editingNewNote = false;
}

void NotesBrowser::on_newNoteBtn_clicked()
{
    _editingNewNote = true;
    ui->noteInput->clear();
}

