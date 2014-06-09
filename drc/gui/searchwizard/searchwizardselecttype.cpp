#include "searchwizardselecttype.h"
#include <QVBoxLayout>
#include "searchwizard.h"
#include <QDebug>


SearchWizardSelectType::SearchWizardSelectType(QWidget *parent)
     : QWizardPage(parent)
{
    setTitle(tr("Select Information Type"));
    setSubTitle(tr("Specify what you want to search for."));
    //     setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

    searchTypeLabel = new QLabel("Search Type:");
    searchTypeComboBox = new QComboBox;
    searchTypeComboBox->addItem("<Select Type>");
    searchTypeComboBox->addItem("Person");
    searchTypeComboBox->addItem("Mediation");
    searchTypeComboBox->addItem("Call Log");
    connect(searchTypeComboBox , SIGNAL(currentIndexChanged(int)),this,SLOT(handleSelectionChanged(int)));
    registerField(FIELD_SEARCH_TYPE + "*", searchTypeComboBox);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    //     groupBoxLayout->addWidget(searchTypeLabel);
    groupBoxLayout->addWidget(searchTypeComboBox);
    setLayout(groupBoxLayout);
}

void SearchWizardSelectType::handleSelectionChanged(int index)
{
    _searchType = searchTypeComboBox->itemText(index);
    qDebug() << "Selected type = " << _searchType;
};
