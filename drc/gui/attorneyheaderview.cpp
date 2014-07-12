#include "attorneyheaderview.h"
#include "ui_attorneyheaderview.h"

AttorneyHeaderView::AttorneyHeaderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttorneyHeaderView)
{
    ui->setupUi(this);
}

AttorneyHeaderView::~AttorneyHeaderView()
{
    delete ui;
}
