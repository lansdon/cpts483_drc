#ifndef MAINMENUFORM_H
#define MAINMENUFORM_H

#include <QWidget>

namespace Ui {
class MainMenuForm;
}

class MainMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuForm(QWidget *parent = 0);
    ~MainMenuForm();

private slots:
    void on_newIntakeBtn_clicked();

    void on_searchBtn_clicked();

    void on_newEvaluationBtn_clicked();

    void on_resWaBtn_clicked();

    void on_monthlyReportBtn_clicked();

private:
    Ui::MainMenuForm *ui;
};

#endif // MAINMENUFORM_H
