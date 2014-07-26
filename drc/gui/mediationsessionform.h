#ifndef MEDIATIONSESSIONFORM_H
#define MEDIATIONSESSIONFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include <vector>
#include "drc_shared/models/mediationprocess.h"
#include "drc_shared/drctypes.h"
#include "Mediator.h"



namespace Ui {
class MediationSessionForm;
}

/*!
 * \brief The MediationSessionForm class
 */
class MediationSessionForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSessionForm(QWidget *parent = 0, MediationSession * MSC = nullptr);
    ~MediationSessionForm();
    /*!
     * \brief setParties
     * \param input
     */
    void setParties(int input);
    /*!
     * \brief updateTabs
     * \param input
     */
    void updateTabs(std::vector<Person *> *input);
    /*!
     * \brief setMediationSession
     * \param value
     */
    void setMediationSession(MediationSession *value);

private slots:
    /*!
     * \brief on_dateTimeEdit_dateTimeChanged
     * \param dateTime
     */
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    /*!
     * \brief SaveSignaled
     */
    void SaveSignaled();
    /*!
     * \brief EditSignaled
     */
    void EditSignaled();
    /*!
     * \brief SetSessionEvent
     * \param arg
     */
    void SetSessionEvent(MediatorArg arg);
    /*!
     * \brief on_stateComboBox_currentIndexChanged
     * \param index
     */
    void on_stateComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_MediatorLineEdit_textEdited
     * \param arg1
     */
    void on_MediatorLineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_Mediator2LineEdit_textEdited
     * \param arg1
     */
    void on_Mediator2LineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_Observe1LineEdit_textEdited
     * \param arg1
     */
    void on_Observe1LineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_Observer2lineEdit_textEdited
     * \param arg1
     */
    void on_Observer2lineEdit_textEdited(const QString &arg1);
    /*!
     * \brief on_dateEdit_userDateChanged
     * \param date
     */
    void on_dateEdit_userDateChanged(const QDate &date);
    /*!
     * \brief on_timeEdit_userTimeChanged
     * \param time
     */
    void on_timeEdit_userTimeChanged(const QTime &time);
    /*!
     * \brief on_outcomeComboBox_currentIndexChanged
     * \param index
     */
    void on_outcomeComboBox_currentIndexChanged(int index);

    void on_shuttleCheckBox_toggled(bool checked);

public slots:
    /*!
     * \brief updateFromTable
     */
    void updateFromTable();
    /*!
     * \brief TestCheckBoxToggled
     * \param value
     */
    void TestCheckBoxToggled(bool value);
private:
    Ui::MediationSessionForm *ui;
    MediationSession *_mediationSession;
//    ClientSessionDataVector _sessionData;
    MediatorId _mediatorid;
    /*!
     * \brief configureFeeTable
     */
    void configureFeeTable();
    /*!
     * \brief PopulateFeeTable
     */
    void PopulateFeeTable();
    /*!
     * \brief configureMediatorTable
     */
    void configureMediatorTable();
    /*!
     * \brief configureAttyAndSupportTable
     */
    void configureAttyAndSupportTable();
    /*!
     * \brief fillFields
     * \param input
     */
    void fillFields(MediationSession *input);
    /*!
     * \brief FillingFields
     */
    bool FillingFields;
    /*!
     * \brief ConfigureComboBoxes
     */
    void ConfigureComboBoxes();
    /*!
     * \brief populateAttyAndSupportTable
     */
    void populateAttyAndSupportTable();
    /*!
     * \brief populateMediatorTable
     */
    void populateMediatorTable();

};

#endif // MEDIATIONSESSIONFORM_H
