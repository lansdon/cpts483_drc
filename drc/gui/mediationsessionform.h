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

class MediationSessionForm : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSessionForm(QWidget *parent = 0, MediationSession * MSC = nullptr);
    ~MediationSessionForm();
    void setParties(int input);
    void updateTabs(std::vector<Person *> *input);
    void setMediationSession(MediationSession *value);

private slots:
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_Fee1LineEdit_textEdited(const QString &arg1);

    void on_Fee1PaidCheckBox_toggled(bool checked);

    void on_Fee2LineEdit_textEdited(const QString &arg1);

    void on_FamilyFeeLineEdit_textEdited(const QString &arg1);

    void on_OtherFeeLineEdit_textEdited(const QString &arg1);

    void on_Fee2PaidCheckBox_toggled(bool checked);

    void on_FamilyFeePaidCheckBox_toggled(bool checked);

    void on_OtherFeePaidCheckBox_toggled(bool checked);

    void on_incomeFee1LineEdit_textEdited(const QString &arg1);

    void on_incomeFee2LineEdit_textEdited(const QString &arg1);

    void on_incomeFeeFamilyLineEdit_textEdited(const QString &arg1);

    void on_incomeFeeOtherLineEdit_textEdited(const QString &arg1);

    void SaveSignaled();
    void EditSignaled();

    void SetSessionEvent(MediatorArg arg);
    void on_supportNumComboBox_currentIndexChanged(int index);

    void on_stateComboBox_currentIndexChanged(int index);

    void on_MediatorLineEdit_textEdited(const QString &arg1);

    void on_Mediator2LineEdit_textEdited(const QString &arg1);

    void on_Observe1LineEdit_textEdited(const QString &arg1);

    void on_Observer2lineEdit_textEdited(const QString &arg1);

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_outcomeComboBox_currentIndexChanged(int index);

public slots:
    void updateFromTable();
    void TestCheckBoxToggled(bool value);
private:
    Ui::MediationSessionForm *ui;
    MediationSession *_mediationSession;
    ClientSessionDataVector _sessionData;
    MediatorId _mediatorid;
    void configureFeeTable();
    void PopulateFeeTable();
    void configureMediatorTable();
    void configureAttyAndSupportTable();
    void fillFields(MediationSession *input);
    bool FillingFields;
    void ConfigureComboBoxes();
    void populateAttyAndSupportTable();

};

#endif // MEDIATIONSESSIONFORM_H
