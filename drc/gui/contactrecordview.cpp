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
    QListWidgetItem *item = new QListWidgetItem();
    QListWidget * test = new QListWidget();
    ui->scrollArea->setWidget(test);
    for( int i =0; i < 10; i++)
    {
        test->setItemWidget(item,new ContactRecordDataView());
        test->addItem(QString::fromStdString(std::to_string(i)));
    }


}

ContactRecordView::~ContactRecordView()
{
    delete ui;
}
