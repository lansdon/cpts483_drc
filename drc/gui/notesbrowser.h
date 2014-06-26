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


private:
    Ui::NotesBrowser *ui;

    MediationNotesVector* _notes;

    void ConfigTable();
    void PopulateTable();

};

#endif // NOTESBROWSER_H
