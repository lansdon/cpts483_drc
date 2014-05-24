#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include <QMainWindow>

namespace Ui {
class DRCClient;
}


// DRC Client
// This is the main entrypoint for the GUI Application
class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

private:
    Ui::DRCClient *ui;
};

#endif // DRCCLIENT_H
