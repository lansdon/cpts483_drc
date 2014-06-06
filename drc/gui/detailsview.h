#ifndef DETAILSVIEW_H
#define DETAILSVIEW_H

#include <QWidget>
#include "mediationsession.h"
#include "childrenview.h"

namespace Ui {
class DetailsView;
}

class DetailsView : public QWidget
{
    Q_OBJECT

public:
    explicit DetailsView(QWidget *parent = 0);
    ~DetailsView();
    void updateTabs(std::vector<Person *> input);

private:
    Ui::DetailsView *ui;
    MediationSession *_localMediationSession;
    ChildrenView *_localChildrenView;
};

#endif // DETAILSVIEW_H
