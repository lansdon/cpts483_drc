#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T19:38:12
#
#-------------------------------------------------

QT       += core gui
QT	+= sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drc
TEMPLATE = app



SOURCES += main.cpp\
    gui/IntakeForm.cpp \
    bl/drcbl.cpp \
    db/drcdb.cpp \
    drc_shared/mediator/AsyncMediatorCall.cpp \
    drc_shared/mediator/Mediator.cpp \
    drc_shared/models/Person.cpp \
    DRCClient.cpp

HEADERS  += \
    gui/IntakeForm.h \
    bl/drcbl.h \
    db/drcdb.h \
    drc_shared/mediator/AsyncMediatorCall.h \
    drc_shared/mediator/Mediator.h \
    drc_shared/mediator/MediatorArg.h \
    drc_shared/mediator/MediatorKeys.h \
    drc_shared/models/Person.h \
    DRCClient.h

FORMS    += \
    DRCClient.ui

CONFIG += c++11
