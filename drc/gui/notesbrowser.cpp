#include "notesbrowser.h"
#include "ui_notesbrowser.h"
#include <QDateTime>
#include <QDebug>
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

    _setNotesCallback = Mediator::Register(MKEY_DOCK_SET_NOTES, [this](MediatorArg arg){SetNotesEvent(arg);});

    ConfigTable();
    PopulateTable();

    if(!notesVec || !notesVec->size())
        _editingNewNote = true; // first time in the browser, it's a new note.
    _isSaved = true;

}

NotesBrowser::~NotesBrowser()
{
    Mediator::Unregister(MKEY_DOCK_SET_NOTES, _setNotesCallback);
    delete ui;
}

void NotesBrowser::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void NotesBrowser::ConfigTable()
{
    if(!_notes) _notes = new MediationNotesVector();

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);

    QStringList header;
    header <<"Date"<<"Note";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: AntiqueWhite; selection-color: Black;}");

    // only stretch note column
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        1, QHeaderView::Stretch);
}

void NotesBrowser::PopulateTable()
{
    try
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
    catch(const std::exception& error)
    {
        QMessageBox msgBox;
        msgBox.setText( "BAM! Notes browser crashed: " + QString(error.what()));
        msgBox.show();
    }
}

void NotesBrowser::SetNotes(MediationNotesVector* notes)
{
    _notes = notes;
    ConfigTable();
    PopulateTable();
}

void NotesBrowser::SetNotesEvent(MediatorArg arg)
{
    MediationNotesVector* notes = arg.getArg<MediationNotesVector*>();
    if(notes)
    {
        ui->noteInput->clear();
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
        int curRow = ui->tableWidget->currentRow();
        if((int)_notes->size() > curRow && curRow >= 0 && !_editingNewNote)
            _notes->at(ui->tableWidget->currentRow())->SetMessage(message);
        // Add a new note
        else _notes->push_back(new Note(message));

        ui->noteInput->clear();
        PopulateTable();
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
        ui->tableWidget->setCurrentCell(-1,-1);
        bool* change = new bool(false);
        Mediator::Call(MKEY_GUI_NOTE_CHANGED,change);
    }

}

void NotesBrowser::on_delNoteBtn_clicked()
{
    if(((int)_notes->size()) > ui->tableWidget->currentIndex().row())
    {
        if(_notes->size() != 1)
            _notes->erase(_notes->begin() + ui->tableWidget->currentIndex().row());
        else
            _notes = new MediationNotesVector();
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
    PopulateTable();
}

void NotesBrowser::on_tableWidget_itemSelectionChanged()
{
    int curRow = ui->tableWidget->currentRow();
    if((int)_notes->size() > curRow && curRow >= 0)
    {
        Note* curNote = _notes->at(curRow);
        ui->noteInput->setText(curNote->GetMessage());
    }
    _editingNewNote = false;
}

void NotesBrowser::on_newNoteBtn_clicked()
{
    _editingNewNote = true;
    ui->noteInput->clear();
}


void NotesBrowser::on_noteInput_textChanged()
{
    bool *change = new bool(true);
    Mediator::Call(MKEY_GUI_NOTE_CHANGED,change);
}
