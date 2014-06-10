#-------------------------------------------------
#
# Project created by QtCreator 2014-06-09T23:36:11
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_bltestsuit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../drc/bl/ \
    ../../drc/drc_shared/ \
    ../../drc/drc_shared/mediator/ \
    ../../drc/drc_shared/models/

SOURCES += tst_bltestsuit.cpp \
    ../../drc/drc_shared/models/Person.cpp \
    ../../drc/bl/personvalidator.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
