#include "intakeform.h"
#include "ui_intakeform.h"

IntakeForm::IntakeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntakeForm)
{
    ui->setupUi(this);
}

IntakeForm::~IntakeForm()
{
    delete ui;
}
