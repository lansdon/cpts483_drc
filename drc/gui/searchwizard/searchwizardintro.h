#ifndef SEARCHWIZARDINTRO_H
#define SEARCHWIZARDINTRO_H

#include <QWizardPage>
#include <QLabel>

class SearchWizardIntro : public QWizardPage
 {
     Q_OBJECT

 public:
     SearchWizardIntro(QWidget *parent = 0);

 private:
     QLabel *label;
 };

#endif // SEARCHWIZARDINTRO_H
