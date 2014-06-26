#-------------------------------------------------
#
# Project created by QtCreator 2014-06-04T01:22:52
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_databasetestsuite
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_databasetestsuite.cpp \
    drcdb.cpp \
    Fruit.cpp \
    Basket.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    DBBaseObject.h \
    drcdb.h \
    Fruit.h \
    Basket.h

CONFIG += C++11
