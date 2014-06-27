#ifndef NOTESBROWSER_H
#define NOTESBROWSER_H

#include <QWidget>
#include "drctypes.h"
#include "MediatorArg.h"

namespace Ui {
class NotesBrowser;
}

class NotesBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit NotesBrowser(QWidget *parent = 0, MediationNotesVector* notesVec = nullptr);
    ~NotesBrowser();

    void SetNotes(MediationNotesVector* notes);
    void SetNotesEvent(MediatorArg arg);

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_saveNoteBtn_clicked();

    void on_delNoteBtn_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_newNoteBtn_clicked();

private:
    Ui::NotesBrowser *ui;

    MediationNotesVector* _notes;

    void ConfigTable();
    void PopulateTable();

    bool _editingNewNote;   // update or save?
};

#endif // NOTESBROWSER_H
