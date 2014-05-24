/********************************************************************************
** Form generated from reading UI file 'DRCClient.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRCCLIENT_H
#define UI_DRCCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DRCClient
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DRCClient)
    {
        if (DRCClient->objectName().isEmpty())
            DRCClient->setObjectName(QStringLiteral("DRCClient"));
        DRCClient->resize(400, 300);
        menuBar = new QMenuBar(DRCClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DRCClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DRCClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DRCClient->addToolBar(mainToolBar);
        centralWidget = new QWidget(DRCClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DRCClient->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DRCClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DRCClient->setStatusBar(statusBar);

        retranslateUi(DRCClient);

        QMetaObject::connectSlotsByName(DRCClient);
    } // setupUi

    void retranslateUi(QMainWindow *DRCClient)
    {
        DRCClient->setWindowTitle(QApplication::translate("DRCClient", "DRCClient", 0));
    } // retranslateUi

};

namespace Ui {
    class DRCClient: public Ui_DRCClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRCCLIENT_H
