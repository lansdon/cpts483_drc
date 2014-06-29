#ifndef PARTYDETAILSFORM_H
#define PARTYDETAILSFORM_H

#include <QWidget>
#include <QKeyEvent>
#include "Person.h"
#include <QLineEdit>
#include "Mediator.h"
#include "MediatorKeys.h"


namespace Ui {
class PersonDetailsForm;
}


class PersonDetailsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonDetailsForm(QWidget *parent = 0, Person* person = nullptr, bool bPopup = false);
    ~PersonDetailsForm();
    void keyPressEvent(QKeyEvent *pe);
    void SetPerson(Person *p);
    Person *GetPerson() { return _person; }

    void SetEditMode(bool editModeOn);
    void ShowButtons(bool showButtons);

private slots:
    void on_emailLineEdit_editingFinished();

    void on_saveButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_firstLineEdit_returnPressed();

    void on_firstLineEdit_editingFinished();

    void on_middleLineEdit_editingFinished();

    void on_lastLineEdit_editingFinished();

    void on_streetLineEdit_editingFinished();

    void on_unitLineEdit_editingFinished();

    void on_cityLineEdit_editingFinished();

    void on_zipLineEdit_editingFinished();

    void on_countyLineEdit_editingFinished();

    void on_stateLineEdit_editingFinished();

    void on_numInHomeLineEdit_editingFinished();

    void on_attorneyLineEdit_editingFinished();

    void on_firstLineEdit_textEdited(const QString &arg1);

    void on_primaryLineEdit_textChanged(const QString &arg1);

    void on_secondaryLineEdit_textChanged(const QString &arg1);
    void on_emailLineEdit_textChanged(const QString &arg1);
    void on_primaryLineEdit_editingFinished();

    void on_secondaryLineEdit_editingFinished();

signals:
    void SaveSignaled();
    void EditSignaled();

    void PersonSaved(Person* person);
    void PersonDeleted(Person* person);

private:
    Ui::PersonDetailsForm *ui;

    Person *_person;

    // This will set the labels based on Person object.
    void UpdateLabels();

    // Validation
    void SetWidgetInvalid(QWidget *widget);
    void SetWidgetValid(QWidget *widget);
    bool ProcessPhoneNumber(const QString& string, QLineEdit *widget);
    bool ProcessEmail(const QString& string, QLineEdit* widget);
    bool ValidateForm();

    bool _editModeOn;

    bool _shouldCleanPersonPointer; // This tracks if person was created internally
    void cleanPerson();             // This will delete _person if it was created internally

    bool _bPopup;

    bool _bShowButtons;

};

#endif // PARTYDETAILSFORM_H
