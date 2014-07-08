#include "mainmenuform.h"
#include "ui_mainmenuform.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "DRCModels.h"
#include <QToolButton>

MainMenuForm::MainMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuForm)
{
    ui->setupUi(this);

    ui->newIntakeBtn->setIcon(QIcon(":images/session_search.jpg"));
    ui->newIntakeBtn->setIconSize(QSize(50, 50));
    ui->searchBtn->setIcon(QIcon(":images/mp_search.jpg"));
    ui->searchBtn->setIconSize(QSize(50, 50));
    ui->newEvaluationBtn->setIcon(QIcon(":images/evaluation.jpg"));
    ui->newEvaluationBtn->setIconSize(QSize(50, 50));
    ui->resWaBtn->setIcon(QIcon(":images/reswalogo.gif"));
    ui->resWaBtn->setIconSize(QSize(50, 50));
    ui->monthlyReportBtn->setIcon(QIcon(":images/report.jpg"));
    ui->monthlyReportBtn->setIconSize(QSize(50, 50));

    ui->logoLabel->setPixmap(QPixmap(":images/drclogo_med.png"));

    ui->frame->setStyleSheet("QFrame#frame {\
                                               border: 2px solid gray;\
                                               border-radius: 5px;\
                                               margin-top: 1.3em;\
                                              }");

}

MainMenuForm::~MainMenuForm()
{
    delete ui;
}

void MainMenuForm::on_newIntakeBtn_clicked()
{
    Mediator::Call(MKEY_GUI_MP_NEW_FORM);
}

void MainMenuForm::on_searchBtn_clicked()
{
    Mediator::Call(MKEY_GUI_SHOW_MEDIATION_BROWSER);
}

void MainMenuForm::on_newEvaluationBtn_clicked()
{
    Mediator::Call(MKEY_GUI_SHOW_EVALUATION);
}

void MainMenuForm::on_resWaBtn_clicked()
{
    Mediator::Call(MKEY_GUI_SHOW_RESWA_REPORT);

}

void MainMenuForm::on_monthlyReportBtn_clicked()
{
    Mediator::Call(MKEY_GUI_SHOW_MONTHLY_REPORT);

}
