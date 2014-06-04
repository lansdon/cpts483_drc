#include "contactrecordview.h"
#include "ui_contactrecordview.h"
#include <QWidget>
#include <QListWidget>

ContactRecordView::ContactRecordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactRecordView)
{
    ui->setupUi(this);
    ui->toolBox->removeItem(0);
    for(int i = 0; i < 100; i++)
        ui->toolBox->addItem(new ContactRecordDataView,"Test");


}

ContactRecordView::~ContactRecordView()
{
    delete ui;
}
