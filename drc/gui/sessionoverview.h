#ifndef SESSIONOVERVIEW_H
#define SESSIONOVERVIEW_H

#include <QWidget>
#include "mediationsession.h"

namespace Ui {
class SessionOverview;
}

class SessionOverview : public QWidget
{
    Q_OBJECT

public:
    explicit SessionOverview(QWidget *parent = 0, MediationSession *mediationSession = nullptr);
    ~SessionOverview();

private:
    Ui::SessionOverview *ui;
    MediationSession *_mediationSession;
    void updateView();
};

#endif // SESSIONOVERVIEW_H
