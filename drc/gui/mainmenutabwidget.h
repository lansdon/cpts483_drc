#ifndef MAINMENUTABWIDGET_H
#define MAINMENUTABWIDGET_H

#include <QTabWidget>
#include "intakeform.h"

namespace Ui {
class MainMenuTabWidget;
}

class MainMenuTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit MainMenuTabWidget(QWidget *parent = 0);
    ~MainMenuTabWidget();

private:
    Ui::MainMenuTabWidget *ui;
};

#endif // MAINMENUTABWIDGET_H
