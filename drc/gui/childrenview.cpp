#include "childrenview.h"
#include "ui_childrenview.h"

ChildrenView::ChildrenView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildrenView)
{
    ui->setupUi(this);
}

ChildrenView::~ChildrenView()
{
    delete ui;
}
