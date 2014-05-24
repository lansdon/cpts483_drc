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
        DRCClient.cpp \
    IntakeForm.cpp \
    Person.cpp

HEADERS  += DRCClient.h \
    IntakeForm.h \
    Person.h

FORMS    += DRCClient.ui
