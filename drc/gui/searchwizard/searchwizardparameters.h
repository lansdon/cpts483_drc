#ifndef SEARCHWIZARDPARAMETERS_H
#define SEARCHWIZARDPARAMETERS_H

#include <QWizardPage>
#include "persondetailsform.h"
#include "mediationprocessview.h"


class SearchWizardParameters : public QWizardPage
 {
     Q_OBJECT

 public:
     SearchWizardParameters(QWidget *parent = 0);

 protected:
     void initializePage();

 private:
    PersonDetailsForm* _personForm;
    MediationProcessView* _mediationForm;

    int _searchType;
 };


#endif // SEARCHWIZARDPARAMETERS_H
