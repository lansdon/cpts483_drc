#include "notesbrowser.h"
#include "ui_notesbrowser.h"
#include <QDateTime>
#include <QDebug>>


class MediationNote
{
    MediationNote(){};

public:
    QDateTime GetCreationDate() { return QDateTime::currentDateTime(); }
    QString GetNote() { return "Sample Note... Stuff goes here. OMG!"; }
};

NotesBrowser::NotesBrowser(QWidget *parent, MediationNotesVector* notesVec)
    : QWidget(parent)
    , ui(new Ui::NotesBrowser)
    , _notes(notesVec)

{
    ui->setupUi(this);

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
    ui->tableWidget->setColumnCount(3);
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

    for (int c = 0; c < ui->tableWidget->horizontalHeader()->count(); ++c)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void NotesBrowser::PopulateTable()
{
    ui->tableWidget->setRowCount(_notes->size());
    for(int row=0; row < (int)_notes->size(); ++row)
    {
        qDebug() << "populate row: " << row;
        //insert data
        MediationNote *note = _notes->at(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(note->GetCreationDate().toString("MM-dd-yyyy")));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(note->GetNote()));
    }
}

void NotesBrowser::SetNotes(MediationNotesVector* notes)
{
    _notes = notes;
    PopulateTable();
}
