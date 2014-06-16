#include "detailsview.h"
#include "ui_detailsview.h"

DetailsView::DetailsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailsView)
{
    ui->setupUi(this);
    _mediationSessionForm = new MediationSessionForm();
    _childrenView = new ChildrenView();
    ui->MediationSessiontabWidget->addTab(_mediationSessionForm,"Session 1");
    ui->ChildrenTabWidget->addTab(_childrenView, "Children");
}

DetailsView::~DetailsView()
{
    delete ui;

}

void DetailsView::updateTabs(PersonVector *input)
{
    _mediationSessionForm->updateTabs(input);
}
