#ifndef SESSIONSVIEW_H
#define SESSIONSVIEW_H

#include <QWidget>
#include "drctypes.h"
#include "drc_shared/models/mediationsession.h"
#include "mediationsessionform.h"

namespace Ui {
class SessionsView;
}

class SessionsView : public QWidget
{
    Q_OBJECT

public:
    explicit SessionsView(QWidget *parent = 0, MediationSessionVector *vec = nullptr);
    ~SessionsView();

private slots:
    void on_addSessionPushButton_clicked();

    void on_sessionsTabWidget_tabCloseRequested(int index);

private:
    Ui::SessionsView *ui;
    MediationSessionVector *_sessions;
    void populate();
};

#endif // SESSIONSVIEW_H
