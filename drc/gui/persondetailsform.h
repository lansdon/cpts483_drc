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
    void on_emailLineEdit_textEdited(const QString &arg1);

    void on_saveButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_firstLineEdit_returnPressed();

    void on_firstLineEdit_textEdited(const QString &arg1);

    void on_middleLineEdit_textEdited(const QString &arg1);

    void on_lastLineEdit_textEdited(const QString &arg1);

    void on_streetLineEdit_textEdited(const QString &arg1);

    void on_unitLineEdit_textEdited(const QString &arg1);

    void on_cityLineEdit_textEdited(const QString &arg1);

    void on_zipLineEdit_textEdited(const QString &arg1);

    void on_stateLineEdit_textEdited(const QString &arg1);

    void on_attorneyLineEdit_textEdited(const QString &arg1);

    void on_primaryLineEdit_textEdited(const QString &arg1);
    void on_primaryExtLineEdit_textEdited(const QString &arg1);

    void on_secondaryLineEdit_textEdited(const QString &arg1);
    void on_secondaryExtLineEdit_textEdited(const QString &arg1);

    void on_adultsInHomeSpinBox_valueChanged(int arg1);

    void on_assistantLineEdit_editingFinished();

    void on_countyComboBox_currentIndexChanged(int index);

    void on_childrenInHomeSpinBox_valueChanged(int arg1);

    void on_attorneyPhoneLineEdit_editingFinished();

    void on_attorneyEmailLineEdit_editingFinished();

    void on_assistantPhoneLineEdit_editingFinished();

    void on_assistantEmailLineEdit_editingFinished();

    void on_assistantNameLineEdit_textEdited(const QString &arg1);

    void on_attorneyPhoneLineEdit_textEdited(const QString &arg1);

    void on_attorneyEmailLineEdit_textEdited(const QString &arg1);

    void on_assistantPhoneLineEdit_textEdited(const QString &arg1);

    void on_assistantEmailLineEdit_textEdited(const QString &arg1);

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

    void configureComboBoxes();

    // Tracking Phone Changes for auto-complete using a map
    std::map<QWidget*, QString> _phoneMap;
};

#endif // PARTYDETAILSFORM_H
