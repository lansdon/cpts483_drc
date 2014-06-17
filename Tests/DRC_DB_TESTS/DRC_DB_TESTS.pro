#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T21:20:02
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_drc_db_tests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app

INCLUDEPATH += ../../drc/drc_shared/models/ \
    ../../drc/db/


SOURCES += tst_drc_db_tests.cpp \
    ../../drc/db/drcdb.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../drc/db/drcdb.h \
    ../../drc/drc_shared/models/DBBaseObject.h
