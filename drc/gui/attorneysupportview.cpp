#include "attorneysupportview.h"
#include "ui_attorneysupportview.h"

AttorneySupportView::AttorneySupportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttorneySupportView)
{
    ui->setupUi(this);
}

AttorneySupportView::~AttorneySupportView()
{
    delete ui;
}
