/********************************************************************************
** Form generated from reading UI file 'drc.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRC_H
#define UI_DRC_H

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

class Ui_drcClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *drcClass)
    {
        if (drcClass->objectName().isEmpty())
            drcClass->setObjectName(QStringLiteral("drcClass"));
        drcClass->resize(600, 400);
        menuBar = new QMenuBar(drcClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        drcClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(drcClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        drcClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(drcClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        drcClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(drcClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        drcClass->setStatusBar(statusBar);

        retranslateUi(drcClass);

        QMetaObject::connectSlotsByName(drcClass);
    } // setupUi

    void retranslateUi(QMainWindow *drcClass)
    {
        drcClass->setWindowTitle(QApplication::translate("drcClass", "drc", 0));
    } // retranslateUi

};

namespace Ui {
    class drcClass: public Ui_drcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRC_H
