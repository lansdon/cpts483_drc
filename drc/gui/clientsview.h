#ifndef CLIENTSVIEW_H
#define CLIENTSVIEW_H

#include <QWidget>
#include "drctypes.h"
#include "persondetailsform.h"

namespace Ui {
class ClientsView;
}

class ClientsView : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsView(QWidget *parent = 0, PartyVector *vec = nullptr);
    ~ClientsView();

private slots:
    void on_pushButton_clicked();

    void on_clientsTabWidget_tabCloseRequested(int index);

private:
    Ui::ClientsView *ui;

    PartyVector *_partyVec;

    void populate();
};

#endif // CLIENTSVIEW_H
