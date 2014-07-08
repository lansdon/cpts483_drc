#ifndef MEDIATIONEVALUATIONVIEW_H
#define MEDIATIONEVALUATIONVIEW_H

#include <QWidget>
#include <QPlainTextEdit>

#include "mediationevaluation.h"
#include "toolbarmanager.h"
#include "Mediator.h"
#include "MediatorKeys.h"

namespace Ui {
class MediationEvaluationView;
}

class MediationEvaluationView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationEvaluationView(QWidget *parent = 0);
    ~MediationEvaluationView();

    MediationEvaluation *getMediationEvaluation() { return &_mediationEvaluation; }


    void setMediationEvaluation(MediationEvaluation *value) { _mediationEvaluation = *value; }



private slots:
    //Tool bar buttons
    void saveEvaluation();
    void closeEvaluation();

    void on_questionTwoComboBox_currentIndexChanged(int index);

    void on_questionOneComboBox_currentIndexChanged(int index);

    void on_questionThreeComboBox_currentIndexChanged(int index);

    void on_questionFourComboBox_currentIndexChanged(int index);

    void on_questionFiveComboBox_currentIndexChanged(int index);

    void on_questionSixComboBox_currentIndexChanged(int index);

    void on_questionSevenComboBox_currentIndexChanged(int index);

    void on_questionEightComboBox_currentIndexChanged(int index);

    void on_MediationDateDateEdit_dateChanged(const QDate &date);

    void on_nameLineEdit_textChanged(const QString &arg1);

    void on_emailLineEdit_textChanged(const QString &arg1);

    void on_phoneDayLineEdit_textChanged(const QString &arg1);

    void on_phoneEveningLineEdit_textChanged(const QString &arg1);
    void on_commentsPlainTextEdit_textChanged();

    void on_promotionalPermissionsComboBox_currentIndexChanged(int index);

    void on_followUpPermissionsComboBox_currentIndexChanged(int index);

private:
    Ui::MediationEvaluationView *ui;
    MediationEvaluation _mediationEvaluation;

    void configComboBoxes();
    void configureToolBar();
};

#endif // MEDIATIONEVALUATIONVIEW_H
