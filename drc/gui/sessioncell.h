#ifndef SESSIONCELL_H
#define SESSIONCELL_H

#include <QWidget>
#include "mediationsession.h"

namespace Ui {
class SessionCell;
}

class SessionCell : public QWidget
{
    Q_OBJECT

public:
    explicit SessionCell(QWidget *parent = 0, MediationSession* session = nullptr);
    ~SessionCell();

     void SetSession(MediationSession* session) { _session = session; Populate(); }
    MediationSession* GetSession() { return _session; }
private:
    Ui::SessionCell *ui;
    MediationSession *_session;

    void Populate();

};

#endif // SESSIONCELL_H
