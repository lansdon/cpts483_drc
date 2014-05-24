#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T19:38:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drc
TEMPLATE = app


SOURCES += main.cpp\
    gui/IntakeForm.cpp \
    gui/DRCClient.cpp \
    Person.cpp

HEADERS  += \
    Person.h \
    gui/IntakeForm.h \
    gui/DRCClient.h

FORMS    += \
    gui/DRCClient.ui
