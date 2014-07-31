#include "DRCClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DRCClient w;
    w.setWindowTitle("Mediation Intake Management Environment");
    w.setWindowIcon(QIcon(":image/drclogo.png"));
    w.show();

    return a.exec();
}
