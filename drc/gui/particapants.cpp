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
