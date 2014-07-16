#include "mediationevaluationview.h"
#include "ui_mediationevaluationview.h"
#include <QMessageBox>



MediationEvaluationView::MediationEvaluationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationEvaluationView)
{
    ui->setupUi(this);
    ui->logoLabel->setPixmap(QPixmap(":images/drclogo.png"));
    ui->MediationDateDateEdit->setDate(QDate::currentDate());
    ui->outterMostGroupBox->setStyleSheet("QGroupBox {border: 2px solid gray; border-radius: 5px; margin-top: 1.3em;}\
                                          QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding:0 13px;}");
    configComboBoxes();
    configureToolBar();
}

MediationEvaluationView::~MediationEvaluationView()
{
    delete ui;
}

void MediationEvaluationView::configComboBoxes()
{
    for(int i = 0; i < 7; i++)
    {
        ui->countyOfMediationComboBox->addItem(StringForCountyIds((CountyIds)i));
    }
    for(int i = 0; i < 5; i++)
    {
        ui->questionOneComboBox->addItem(QString::number(i+1));
    }
    for(int i = 0; i < 4; ++i)
    {

        ui->questionTwoComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionThreeComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionFourComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionFiveComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionSixComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionSevenComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->questionEightComboBox->addItem(StringForEvaluationAnswers((EvaluationAnswers)i));
        ui->promotionalPermissionsComboBox->addItem("");
    }
    ui->promotionalPermissionsComboBox->setItemText(EVALUATION_ANSWERS_NO_ANSWER,StringForEvaluationAnswers(EVALUATION_ANSWERS_NO_ANSWER));
    ui->promotionalPermissionsComboBox->setItemText(1,"Yes without name");
    ui->promotionalPermissionsComboBox->setItemText(2,"Yes with name");
    ui->promotionalPermissionsComboBox->setItemText(3,"No");
    ui->followUpPermissionsComboBox->addItem("No Answer");
    ui->followUpPermissionsComboBox->addItem("Yes");
    ui->followUpPermissionsComboBox->addItem("No");

}

void MediationEvaluationView::configureToolBar()
{
    ToolbarManager& toolbar = ToolbarManager::Instance();
    toolbar.Clear();
    toolbar.AddAction("Save Evaluation", this, SLOT(saveEvaluation()), QIcon(":images/save.png"));
    toolbar.GetToolbar()->addSeparator();
    toolbar.AddAction("Close Evaluation", this, SLOT(closeEvaluation()), QIcon(":images/close.jpg"));
    toolbar.GetToolbar()->addSeparator();
}

void MediationEvaluationView::saveEvaluation()
{
    if(_mediationEvaluation.getCountyOfMediation() == COUNTY_NONE)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("No county of mediation selected.");
        msgBox.exec();
    }
    else
    {
        Mediator::Call(MKEY_GUI_SAVE_EVALUATION, &_mediationEvaluation);
        Mediator::Call(MKEY_GUI_ENABLE_MENUS);
    }

}

void MediationEvaluationView::closeEvaluation()
{
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}

void MediationEvaluationView::on_questionOneComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ1(index);
}

void MediationEvaluationView::on_questionTwoComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ2((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionThreeComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ3((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionFourComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ4((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionFiveComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ5((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionSixComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ6((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionSevenComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ7((EvaluationAnswers)index);
}

void MediationEvaluationView::on_questionEightComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setQ8((EvaluationAnswers)index);
}

void MediationEvaluationView::on_MediationDateDateEdit_dateChanged(const QDate &date)
{
    _mediationEvaluation.setMediationDate(date);
}

void MediationEvaluationView::on_nameLineEdit_textChanged(const QString &arg1)
{
    _mediationEvaluation.setName(arg1);
}

void MediationEvaluationView::on_emailLineEdit_textChanged(const QString &arg1)
{
    _mediationEvaluation.setEmail(arg1);
}

void MediationEvaluationView::on_phoneDayLineEdit_textChanged(const QString &arg1)
{
    _mediationEvaluation.setDayPhone(arg1);
}

void MediationEvaluationView::on_phoneEveningLineEdit_textChanged(const QString &arg1)
{
    _mediationEvaluation.setEveningPhone(arg1);
}

void MediationEvaluationView::on_commentsPlainTextEdit_textChanged()
{
    _mediationEvaluation.setComments(ui->commentsPlainTextEdit->toPlainText());
}

void MediationEvaluationView::on_promotionalPermissionsComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setPromoPermissions((EvaluationAnswers)index);
}

void MediationEvaluationView::on_followUpPermissionsComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setCallBackPermissions((EvaluationAnswers)index);
}

void MediationEvaluationView::on_countyOfMediationComboBox_currentIndexChanged(int index)
{
    _mediationEvaluation.setCountyOfMediation((CountyIds)index);
}
