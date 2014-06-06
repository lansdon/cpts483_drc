#ifndef MEDIATIONSESSION_H
#define MEDIATIONSESSION_H

#include <QWidget>
#include "attorneyandsupportformediationsessionview.h"
#include <vector>
#include "drc_shared/models/Person.h"
namespace Ui {
class MediationSession;
}

class MediationSession : public QWidget
{
    Q_OBJECT

public:
    explicit MediationSession(QWidget *parent = 0);
    ~MediationSession();
    void setParties(int input);
    void updateTabs(std::vector<Person *> input);

private:
    Ui::MediationSession *ui;
    std::vector<AttorneyAndSupportForMediationSessionView *> _attorneyAndSupportVector;
};

#endif // MEDIATIONSESSION_H
