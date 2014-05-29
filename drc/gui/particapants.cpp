#include "particapants.h"
#include "ui_particapants.h"

Particapants::Particapants(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Particapants)
{
    ui->setupUi(this);
}

Particapants::~Particapants()
{
    delete ui;
}

QString Particapants::getName()
{
    return ui->nameLineEditPar->text();
}

void Particapants::setName(std::string str)
{
    ui->nameLineEditPar->setText(QString::fromStdString(str));
}
