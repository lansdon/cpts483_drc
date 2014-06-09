#include "searchwizardparameters.h"
#include "searchwizard.h"
#include <QVBoxLayout>
#include <QDebug>

SearchWizardParameters::SearchWizardParameters(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Search Parameters");
    setSubTitle("Enter fields to search with. More parameters will result in fewer results.");
//    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo2.png"));


}

void SearchWizardParameters::initializePage()
 {
    QVBoxLayout* layout = new QVBoxLayout();

    _searchType = field(FIELD_SEARCH_TYPE).toInt();
    qDebug() << "Search type = " << _searchType;
    switch(_searchType)
    {
    case SEARCH_T_CALL_LOG:

        break;

    case SEARCH_T_MEDIATION:
            _mediationForm = new MediationProcessView(this);
            layout->addWidget(_mediationForm);
        break;

    case SEARCH_T_PERSON:
            _personForm = new PersonDetailsForm(this);
            layout->addWidget(_personForm);
        break;

    default:

        break;
    }
    setLayout(layout);
 }
