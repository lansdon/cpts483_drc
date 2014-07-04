#include "mediationobserverview.h"
#include "ui_mediationobserverview.h"

MediationObserverView::MediationObserverView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediationObserverView)
{
    ui->setupUi(this);
}

MediationObserverView::~MediationObserverView()
{
    delete ui;
}
