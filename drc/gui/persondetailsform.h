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

/*!
 * \brief The PersonDetailsForm class
 */
class PersonDetailsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonDetailsForm(QWidget *parent = 0, Person* person = nullptr, bool bPopup = false);
    ~PersonDetailsForm();
    /*!
     * \brief keyPressEvent
     * \param pe
     */
    void keyPressEvent(QKeyEvent *pe);
    /*!
     * \brief SetPerson
     * \param p
     */
    void SetPerson(Person *p);
    /*!
     * \brief GetPerson
     * \return
     */
    Person *GetPerson() { return _person; }
    /*!
     * \brief SetEditMode
     * \param editModeOn
     */
    void SetEditMode(bool editModeOn);
    /*!
     * \brief ShowButtons
     * \param showButtons
     */
    void ShowButtons(bool showButtons);

private slots:
    /*!
     * \brief on_emailLineEdit_textEdited
     * \param arg1
     */
    void on_emailLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_saveButton_clicked
     */
    void on_saveButton_clicked();
    /*!
     * \brief on_editButton_clicked
     */
    void on_editButton_clicked();
    /*!
     * \brief on_deleteButton_clicked
     */
    void on_deleteButton_clicked();
    /*!
     * \brief on_firstLineEdit_returnPressed
     */
    void on_firstLineEdit_returnPressed();
    /*!
     * \brief on_firstLineEdit_textEdited
     * \param arg1
     */
    void on_firstLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_middleLineEdit_textEdited
     * \param arg1
     */
    void on_middleLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_lastLineEdit_textEdited
     * \param arg1
     */
    void on_lastLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_streetLineEdit_textEdited
     * \param arg1
     */
    void on_streetLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_unitLineEdit_textEdited
     * \param arg1
     */
    void on_unitLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_cityLineEdit_textEdited
     * \param arg1
     */
    void on_cityLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_zipLineEdit_textEdited
     * \param arg1
     */
    void on_zipLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_stateLineEdit_textEdited
     * \param arg1
     */
    void on_stateLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_attorneyLineEdit_textEdited
     * \param arg1
     */
    void on_attorneyLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_primaryLineEdit_textEdited
     * \param arg1
     */
    void on_primaryLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_primaryExtLineEdit_textEdited
     * \param arg1
     */
    void on_primaryExtLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_secondaryLineEdit_textEdited
     * \param arg1
     */
    void on_secondaryLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_secondaryExtLineEdit_textEdited
     * \param arg1
     */
    void on_secondaryExtLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_adultsInHomeSpinBox_valueChanged
     * \param arg1
     */
    void on_adultsInHomeSpinBox_valueChanged(int arg1);
    /*!
     * \brief on_assistantLineEdit_editingFinished
     */
    void on_assistantLineEdit_editingFinished();
    /*!
     * \brief on_countyComboBox_currentIndexChanged
     * \param index
     */
    void on_countyComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_childrenInHomeSpinBox_valueChanged
     * \param arg1
     */
    void on_childrenInHomeSpinBox_valueChanged(int arg1);
    /*!
     * \brief on_attorneyPhoneLineEdit_editingFinished
     */
    void on_attorneyPhoneLineEdit_editingFinished();
    /*!
     * \brief on_attorneyEmailLineEdit_editingFinished
     */
    void on_attorneyEmailLineEdit_editingFinished();
    /*!
     * \brief on_assistantPhoneLineEdit_editingFinished
     */
    void on_assistantPhoneLineEdit_editingFinished();
    /*!
     * \brief on_assistantEmailLineEdit_editingFinished
     */
    void on_assistantEmailLineEdit_editingFinished();
    /*!
     * \brief on_assistantNameLineEdit_textEdited
     * \param arg1
     */
    void on_assistantNameLineEdit_textEdited(const QString &arg1);

signals:
    /*!
     * \brief SaveSignaled
     */
    void SaveSignaled();
    /*!
     * \brief EditSignaled
     */
    void EditSignaled();
    /*!
     * \brief PersonSaved
     * \param person
     */
    void PersonSaved(Person* person);
    /*!
     * \brief PersonDeleted
     * \param person
     */
    void PersonDeleted(Person* person);

private:
    Ui::PersonDetailsForm *ui;

    Person *_person;

    // This will set the labels based on Person object.
    /*!
     * \brief UpdateLabels
     */
    void UpdateLabels();

    // Validation
    /*!
     * \brief SetWidgetInvalid
     * \param widget
     */
    void SetWidgetInvalid(QWidget *widget);
    /*!
     * \brief SetWidgetValid
     * \param widget
     */
    void SetWidgetValid(QWidget *widget);
    /*!
     * \brief ProcessPhoneNumber
     * \param string
     * \param widget
     * \return
     */
    bool ProcessPhoneNumber(const QString& string, QLineEdit *widget);
    /*!
     * \brief ProcessEmail
     * \param string
     * \param widget
     * \return
     */
    bool ProcessEmail(const QString& string, QLineEdit* widget);
    /*!
     * \brief ValidateForm
     * \return
     */
    bool ValidateForm();

    bool _editModeOn;

    bool _shouldCleanPersonPointer; // This tracks if person was created internally
    /*!
     * \brief cleanPerson
     */
    void cleanPerson();             // This will delete _person if it was created internally

    bool _bPopup;

    bool _bShowButtons;
    /*!
     * \brief configureComboBoxes
     */
    void configureComboBoxes();

};

#endif // PARTYDETAILSFORM_H
