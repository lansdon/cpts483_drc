#ifndef SESSIONOVERVIEW_H
#define SESSIONOVERVIEW_H

#include <QWidget>
#include "mediationsession.h"
#include "drctypes.h"

namespace Ui {
class SessionOverview;
}

class SessionOverview : public QWidget
{
    Q_OBJECT

public:
    explicit SessionOverview(QWidget *parent = 0, MediationSessionVector *mediationSessionVector = nullptr);
    ~SessionOverview();
    void setNumberOfSessions(uint value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SessionOverview *ui;
    MediationSessionVector *_mediationSessionVector;
    uint _numberOfSessions;
    void updateView();
};

#endif // SESSIONOVERVIEW_H
