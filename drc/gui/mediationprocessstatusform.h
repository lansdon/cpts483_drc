#ifndef MEDIATIONPROCESSSTATUSFORM_H
#define MEDIATIONPROCESSSTATUSFORM_H

#include <QWidget>
#include "mediationprocess.h"
#include "Mediator.h"
#include "MediatorKeys.h"

namespace Ui {
class MediationProcessStatusForm;
}

/*!
 * \brief The MediationProcessStatusForm class
 */
class MediationProcessStatusForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationProcessStatusForm(QWidget *parent = 0, MediationProcess* mediationProcess = nullptr);
    ~MediationProcessStatusForm();
    /*!
     * \brief setMediationProcess
     * \param value
     */
    void setMediationProcess(MediationProcess* value);
    /*!
     * \brief SetStatusLabel
     * \param message
     * \param isError
     */
    void SetStatusLabel(QString message, bool isError = false);
    /*!
     * \brief SetSavedLabel
     * \param isSaved
     */
    void SetSavedLabel(bool isSaved);
    /*!
     * \brief Update
     */
    void Update();

private slots:
    /*!
     * \brief on_conflictComboBox_currentIndexChanged
     * \param index
     */
    void on_conflictComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_statusComboBox_currentIndexChanged
     * \param index
     */
    void on_statusComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_countyComboBox_currentIndexChanged
     * \param index
     */
    void on_countyComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_referralComboBox_currentIndexChanged
     * \param index
     */
    void on_referralComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_courtCheckBox_clicked
     */
    void on_courtCheckBox_clicked();
    /*!
     * \brief on_courtTypeComboBox_currentIndexChanged
     * \param index
     */
    void on_courtTypeComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_courDateTimeEdit_dateTimeChanged
     * \param dateTime
     */
    void on_courDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    /*!
     * \brief on_courtOrderComboBox_currentIndexChanged
     * \param index
     */
    void on_courtOrderComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_expirationDateTimeEdit_dateTimeChanged
     * \param dateTime
     */
    void on_expirationDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    /*!
     * \brief on_inquiryTypeComboBox_currentIndexChanged
     * \param index
     */
    void on_inquiryTypeComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_infoOnlyCheckBox_toggled
     * \param checked
     */
    void on_infoOnlyCheckBox_toggled(bool checked);
    /*!
     * \brief on_spanishCheckBox_clicked
     * \param checked
     */
    void on_spanishCheckBox_clicked(bool checked);
    /*!
     * \brief on_regularRadioButton_clicked
     */
    void on_regularRadioButton_clicked();
    /*!
     * \brief on_facilitationRadioButton_clicked
     */
    void on_facilitationRadioButton_clicked();
    /*!
     * \brief on_phoneRadioButton_clicked
     */
    void on_phoneRadioButton_clicked();

    void on_mediationClauseCheckBox_toggled(bool checked);

    void on_coachingRadioButton_clicked();

    void on_courtOrderLineEdit_textEdited(const QString &arg1);

private:
    Ui::MediationProcessStatusForm *ui;
    bool _loading;
    MediationProcess* _mediationProcess;

    /*!
     * \brief ConfigureComboBoxes
     */
    void ConfigureComboBoxes(); // Sets the values based on enums.
    /*!
     * \brief MPSaveFinished
     * \param arg
     */
    void MPSaveFinished(MediatorArg arg);
    /*!
     * \brief sessionTypeDisplay
     */
    void sessionTypeDisplay();
    /*!
     * \brief updateSessionType
     */
    void updateSessionType();

    MediatorId _SavePendingCallbackId;      // use to unregister callbacks
    MediatorId _PersistMPDoneCallbackId;    // use to unregister callbacks
    MediatorId _LoadMPCallbackId;           // use to unregister callbacks

signals:
    /*!
     * \brief hovered
     */
    void hovered();
};

#endif // MEDIATIONPROCESSSTATUSFORM_H
