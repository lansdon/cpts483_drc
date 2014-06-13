#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include "attorneyandsupportformediationsessionview.h"
#include <vector>
#include "drc_shared/models/Person.h"
#include "drc_shared/models/mediationsessionclass.h"
#include "drc_shared/drctypes.h"

namespace Ui {
class MediationSession;
}

class MediationSession : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSession(QWidget *parent = 0,MediationSessionClassVector * MSC = nullptr);
    ~MediationSession();
    void setParties(int input);
    void updateTabs(std::vector<Person *> *input);
    void setMediationSessionClassVector(MediationSessionClassVector *value);

private slots:
    void on_CancelledRadioButton_toggled(bool checked);

    void on_PendingRadioButton_toggled(bool checked);

    void on_confirmedRadioButton_toggled(bool checked);

    void on_rescheduledRadioButton_toggled(bool checked);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_Fee1LineEdit_editingFinished();

    void on_Fee1PaidCheckBox_toggled(bool checked);

    void on_sessiontTableWidget_itemSelectionChanged();

    void on_sessiontTableWidget_doubleClicked(const QModelIndex &index);

    void on_Fee2LineEdit_editingFinished();

    void on_FamilyFeeLineEdit_editingFinished();

    void on_OtherFeeLineEdit_editingFinished();

    void on_Fee2PaidCheckBox_toggled(bool checked);

    void on_FamilyFeePaidCheckBox_toggled(bool checked);

    void on_OtherFeePaidCheckBox_toggled(bool checked);

    void on_incomeFee1LineEdit_editingFinished();

    void on_incomeFee2LineEdit_editingFinished();

    void on_incomeFeeFamilyLineEdit_editingFinished();

    void on_incomeFeeOtherLineEdit_editingFinished();

    void on_mediator1EditPushButton_clicked();

    void on_mediator2EditPushButton_clicked();

    void on_observer1EditPushButton_clicked();

    void on_observer2EditPushButton_clicked();

    void deletePersonContact(Person *value);

    void savePersonContact(Person *value);

private:
    Ui::MediationSession *ui;
    std::vector<AttorneyAndSupportForMediationSessionView *> *_attorneyAndSupportVector;
    MediationSessionClassVector *_localMediationSessionClassVector;
    QTableWidget *_sessionTable;
    QStringList _sessionTableHeader;
    void configSessionTable();
    void PopulateSessionTable();
    void fillFields(MediationSessionClass *input);
    int sessionCurrentRow;
    bool FillingFields;

};

#endif // MEDIATIONSESSION_H
