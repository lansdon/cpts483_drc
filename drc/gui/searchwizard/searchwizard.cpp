#include "searchwizard.h"
#include "searchwizardintro.h"
#include "searchwizardselecttype.h"
#include "searchwizardparameters.h"
#include "searchwizardresults.h"


SearchWizard::SearchWizard(QWidget *parent) :
    QWizard(parent)
{
    addPage(new SearchWizardIntro);
    addPage(new SearchWizardSelectType);
    addPage(new SearchWizardParameters);
    addPage(new SearchWizardResults);

    setWindowTitle(tr("Search Wizard"));
    setWindowState(Qt::WindowMaximized);
}


void SearchWizard::accept()
{
//    QByteArray className = field("className").toByteArray();
//    QByteArray baseClass = field("baseClass").toByteArray();
//    QByteArray macroName = field("macroName").toByteArray();
//    QByteArray baseInclude = field("baseInclude").toByteArray();

//    QString outputDir = field("outputDir").toString();
//    QString header = field("header").toString();
//    QString implementation = field("implementation").toString();
//    ...
//    QDialog::accept();
}
