#ifndef DETAILSVIEW_H
#define DETAILSVIEW_H

#include <QWidget>
#include "mediationsessionform.h"
#include "childrenview.h"
#include "drctypes.h"

namespace Ui {
class DetailsView;
}

class DetailsView : public QWidget
{
    Q_OBJECT

public:
    explicit DetailsView(QWidget *parent = 0);
    ~DetailsView();
    void updateTabs(PersonVector *input);

private:
    Ui::DetailsView *ui;
    MediationSessionForm *_mediationSessionForm;
    ChildrenView *_childrenView;
};

#endif // DETAILSVIEW_H
