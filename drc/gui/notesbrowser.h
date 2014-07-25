#ifndef NOTESBROWSER_H
#define NOTESBROWSER_H

#include <QWidget>
#include "drctypes.h"
#include "MediatorArg.h"
#include "Mediator.h"

namespace Ui {
class NotesBrowser;
}

/*!
 * \brief The NotesBrowser class
 */
class NotesBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit NotesBrowser(QWidget *parent = 0, MediationNotesVector* notesVec = nullptr);
    ~NotesBrowser();
    /*!
     * \brief SetNotes
     * \param notes
     */
    void SetNotes(MediationNotesVector* notes);
    /*!
     * \brief SetNotesEvent
     * \param arg
     */
    void SetNotesEvent(MediatorArg arg);

private slots:
    /*!
     * \brief on_tableWidget_doubleClicked
     * \param index
     */
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    /*!
     * \brief on_saveNoteBtn_clicked
     */
    void on_saveNoteBtn_clicked();
    /*!
     * \brief on_delNoteBtn_clicked
     */
    void on_delNoteBtn_clicked();
    /*!
     * \brief on_tableWidget_itemSelectionChanged
     */
    void on_tableWidget_itemSelectionChanged();
    /*!
     * \brief on_newNoteBtn_clicked
     */
    void on_newNoteBtn_clicked();

private:
    Ui::NotesBrowser *ui;

    MediationNotesVector* _notes;
    /*!
     * \brief ConfigTable
     */
    void ConfigTable();
    /*!
     * \brief PopulateTable
     */
    void PopulateTable();
    /*!
     * \brief _editingNewNote
     */
    bool _editingNewNote;   // update or save?

    MediatorId _setNotesCallback;

};

#endif // NOTESBROWSER_H
