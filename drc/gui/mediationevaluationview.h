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

/*!
 * \brief The MediationEvaluationView class
 */
class MediationEvaluationView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationEvaluationView(QWidget *parent = 0);
    ~MediationEvaluationView();
    /*!
     * \brief getMediationEvaluation
     * \return
     */
    MediationEvaluation *getMediationEvaluation() { return &_mediationEvaluation; }
    /*!
     * \brief setMediationEvaluation
     * \param value
     */
    void setMediationEvaluation(MediationEvaluation *value) { _mediationEvaluation = *value; }

private slots:
    //Tool bar buttons
    /*!
     * \brief saveEvaluation
     */
    void saveEvaluation();
    /*!
     * \brief closeEvaluation
     */
    void closeEvaluation();
    /*!
     * \brief on_questionTwoComboBox_currentIndexChanged
     * \param index
     */
    void on_questionTwoComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionOneComboBox_currentIndexChanged
     * \param index
     */
    void on_questionOneComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionThreeComboBox_currentIndexChanged
     * \param index
     */
    void on_questionThreeComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionFourComboBox_currentIndexChanged
     * \param index
     */
    void on_questionFourComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionFiveComboBox_currentIndexChanged
     * \param index
     */
    void on_questionFiveComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionSixComboBox_currentIndexChanged
     * \param index
     */
    void on_questionSixComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionSevenComboBox_currentIndexChanged
     * \param index
     */
    void on_questionSevenComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_questionEightComboBox_currentIndexChanged
     * \param index
     */
    void on_questionEightComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_MediationDateDateEdit_dateChanged
     * \param date
     */
    void on_MediationDateDateEdit_dateChanged(const QDate &date);
    /*!
     * \brief on_nameLineEdit_textChanged
     * \param arg1
     */
    void on_nameLineEdit_textChanged(const QString &arg1);
    /*!
     * \brief on_emailLineEdit_textChanged
     * \param arg1
     */
    void on_emailLineEdit_textChanged(const QString &arg1);
    /*!
     * \brief on_phoneDayLineEdit_textChanged
     * \param arg1
     */
    void on_phoneDayLineEdit_textChanged(const QString &arg1);
    /*!
     * \brief on_phoneEveningLineEdit_textChanged
     * \param arg1
     */
    void on_phoneEveningLineEdit_textChanged(const QString &arg1);
    /*!
     * \brief on_commentsPlainTextEdit_textChanged
     */
    void on_commentsPlainTextEdit_textChanged();
    /*!
     * \brief on_promotionalPermissionsComboBox_currentIndexChanged
     * \param index
     */
    void on_promotionalPermissionsComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_followUpPermissionsComboBox_currentIndexChanged
     * \param index
     */
    void on_followUpPermissionsComboBox_currentIndexChanged(int index);
    /*!
     * \brief on_countyOfMediationComboBox_currentIndexChanged
     * \param index
     */
    void on_countyOfMediationComboBox_currentIndexChanged(int index);

private:
    Ui::MediationEvaluationView *ui;
    MediationEvaluation _mediationEvaluation;

    /*!
     * \brief configComboBoxes
     */
    void configComboBoxes();
    /*!
     * \brief configureToolBar
     */
    void configureToolBar();
};

#endif // MEDIATIONEVALUATIONVIEW_H
