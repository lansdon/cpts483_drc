#include "nosessionsview.h"
#include "ui_nosessionsview.h"

NoSessionsView::NoSessionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoSessionsView)
{
    ui->setupUi(this);
}

NoSessionsView::~NoSessionsView()
{
    delete ui;
}

void NoSessionsView::on_clickToAddSessionPushButton_clicked()
{
    //send signal to add a session to the mediation vector
    emit sendAddNewSession();
}
