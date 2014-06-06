#include "attorneyandsupportformediationsessionview.h"
#include "ui_attorneyandsupportformediationsessionview.h"

AttorneyAndSupportForMediationSessionView::AttorneyAndSupportForMediationSessionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttorneyAndSupportForMediationSessionView)
{
    ui->setupUi(this);
    _attorneyFieldEdited = false;
}

AttorneyAndSupportForMediationSessionView::~AttorneyAndSupportForMediationSessionView()
{
    delete ui;
}

void AttorneyAndSupportForMediationSessionView::setAttorney(QString input)
{
    if(!_attorneyFieldEdited)
        ui->attorneyLineEdit->setText(input);
    ui->attorneyLineEdit->repaint();
}

void AttorneyAndSupportForMediationSessionView::setSupport(QString input)
{
    ui->supportLineEdit->setText(input);
    ui->supportLineEdit->repaint();
}

std::string AttorneyAndSupportForMediationSessionView::getAttorney()
{
    return (ui->attorneyLineEdit->text().toUtf8().constData());
}

std::string AttorneyAndSupportForMediationSessionView::getSupport()
{
    return (ui->supportLineEdit->text().toUtf8().constData());
}

void AttorneyAndSupportForMediationSessionView::on_attorneyLineEdit_textChanged(const QString &arg1)
{
    _attorneyFieldEdited = true;
}
