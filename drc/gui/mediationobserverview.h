#ifndef MEDIATIONOBSERVERVIEW_H
#define MEDIATIONOBSERVERVIEW_H

#include <QWidget>

namespace Ui {
class MediationObserverView;
}

class MediationObserverView : public QWidget
{
    Q_OBJECT

public:
    explicit MediationObserverView(QWidget *parent = 0);
    ~MediationObserverView();

private:
    Ui::MediationObserverView *ui;
};

#endif // MEDIATIONOBSERVERVIEW_H
