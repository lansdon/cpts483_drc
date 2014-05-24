#include "gui/DRCClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DRCClient w;
    w.show();

    return a.exec();
}
