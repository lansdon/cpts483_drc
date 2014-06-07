#ifndef PARTYDETAILSFORM_H
#define PARTYDETAILSFORM_H

#include <QWidget>
#include "Person.h"
#include <QLineEdit>


namespace Ui {
class PartyDetailsForm;
}


class PartyDetailsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyDetailsForm(QWidget *parent = 0, Person* person = nullptr);
    ~PartyDetailsForm();

    void SetPerson(Person *p);
    Person *GetPerson() { return _person; }
private slots:
    void on_emailLineEdit_textChanged(const QString &arg1);

    void on_workLineEdit_textChanged(const QString &arg1);

    void on_homeLineEdit_textChanged(const QString &arg1);

    void on_mobileLineEdit_textChanged(const QString &arg1);

    void on_saveButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_firstLineEdit_returnPressed();

private:
    Ui::PartyDetailsForm *ui;

    Person *_person;

    // This will set the labels based on Person object.
    void UpdateLabels();

    // Validation
    void SetWidgetInvalid(QWidget *widget);
    void SetWidgetValid(QWidget *widget);
    bool ProcessPhoneNumber(const QString& string, QLineEdit *widget);
    bool ProcessEmail(const QString& string, QLineEdit* widget);
    void SetEditMode(bool editModeOn);
    bool ValidateForm();

    bool _editModeOn;

    bool _shouldCleanPersonPointer; // This tracks if person was created internally
    void cleanPerson();             // This will delete _person if it was created internally

};

#endif // PARTYDETAILSFORM_H
