#include "contactrecorddataview.h"
#include "ui_contactrecorddataview.h"

ContactRecordDataView::ContactRecordDataView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactRecordDataView)
{
    ui->setupUi(this);
}

ContactRecordDataView::~ContactRecordDataView()
{
    delete ui;
}
