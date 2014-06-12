#include "detailsview.h"
#include "ui_detailsview.h"

DetailsView::DetailsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailsView)
{
    ui->setupUi(this);
    _localMediationSession = new MediationSession();
    _localChildrenView = new ChildrenView();
    ui->MediationSessiontabWidget->addTab(_localMediationSession,"Session 1");
    ui->ChildrenTabWidget->addTab(_localChildrenView, "Children");
}

DetailsView::~DetailsView()
{
    delete ui;

}

void DetailsView::updateTabs(std::vector<Person *> *input)
{
    _localMediationSession->updateTabs(input);
}
