#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T22:40:28
#
# Look ma! I'm making tests!!  -LP
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_guitests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG  += c++11

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../drc/bl/ \
    ../../drc/db/ \
    ../../drc/drc_shared/ \
    ../../drc/drc_shared/mediator/ \
    ../../drc/drc_shared/models/ \
    ../../drc/gui/

HEADERS += \
    AutoTest.h \
    mediatortests.h \
    ../../drc/drc_shared/mediator/Mediator.h

SOURCES += \
    main.cpp \
    mediatortests.cpp \
    ../../drc/drc_shared/mediator/Mediator.cpp
