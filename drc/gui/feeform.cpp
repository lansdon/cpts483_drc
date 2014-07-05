#include "feeform.h"
#include "ui_feeform.h"

FeeForm::FeeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeeForm)
{
    ui->setupUi(this);
}

FeeForm::~FeeForm()
{
    delete ui;
}
