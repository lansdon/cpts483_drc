#include "partysummaryform.h"
#include "ui_partysummaryform.h"
#include "party.h"


PartySummaryForm::PartySummaryForm(QWidget *parent, Party* party) :
    QWidget(parent),
    ui(new Ui::PartySummaryForm),
    _party(party)
{
    ui->setupUi(this);

    ui->childrenLabel->setText(QString::number(_party->GetAffectedChildren()));
    ui->fullnameLabel->setText(_party->GetPrimary()->FullName());
    ui->spanishCheckbox->setChecked(_party->GetSpanishRequired());
}

PartySummaryForm::~PartySummaryForm()
{
    delete ui;
}
