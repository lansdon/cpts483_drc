#ifndef NOSESSIONSVIEW_H
#define NOSESSIONSVIEW_H

#include <QWidget>

namespace Ui {
class NoSessionsView;
}

class NoSessionsView : public QWidget
{
    Q_OBJECT

public:
    explicit NoSessionsView(QWidget *parent = 0);
    ~NoSessionsView();

private slots:
    void on_clickToAddSessionPushButton_clicked();

private:
    Ui::NoSessionsView *ui;
signals:
    void sendAddNewSession();
};

#endif // NOSESSIONSVIEW_H
