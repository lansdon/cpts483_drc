#ifndef MAINMENUFORM_H
#define MAINMENUFORM_H

#include <QWidget>

namespace Ui {
class MainMenuForm;
}

/*!
 * \brief The MainMenuForm class
 */
class MainMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuForm(QWidget *parent = 0);
    ~MainMenuForm();

private slots:
    /*!
     * \brief on_newIntakeBtn_clicked
     */
    void on_newIntakeBtn_clicked();
    /*!
     * \brief on_searchBtn_clicked
     */
    void on_searchBtn_clicked();
    /*!
     * \brief on_newEvaluationBtn_clicked
     */
    void on_newEvaluationBtn_clicked();
    /*!
     * \brief on_resWaBtn_clicked
     */
    void on_resWaBtn_clicked();
    /*!
     * \brief on_monthlyReportBtn_clicked
     */
    void on_monthlyReportBtn_clicked();

private:
    Ui::MainMenuForm *ui;
};

#endif // MAINMENUFORM_H
