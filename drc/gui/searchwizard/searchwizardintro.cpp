#include "searchwizardintro.h"

#include "QVBoxLayout"

SearchWizardIntro::SearchWizardIntro(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Introduction"));
     setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

     label = new QLabel(tr("This wizard will walk you through searching for information."));
     label->setWordWrap(true);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
     setLayout(layout);
 }
