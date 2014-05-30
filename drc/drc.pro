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
    bl/drcbl.cpp \
    db/drcdb.cpp \    
    drc_shared/mediator/Mediator.cpp \
    drc_shared/mediator/AsyncMediatorCall.cpp \
    drc_shared/models/Person.cpp \
    DRCClient.cpp \
    drc_shared/models/Intake.cpp \
    gui/fruitnameform.cpp \
    gui/intakeform.cpp \
    gui/mainmenutabwidget.cpp \
    gui/particapants.cpp

HEADERS  += \
    bl/drcbl.h \
    db/drcdb.h \
    drc_shared/mediator/Mediator.h \
    drc_shared/mediator/MediatorArg.h \
    drc_shared/mediator/MediatorKeys.h \
    drc_shared/mediator/AsyncMediatorCall.h \
    drc_shared/models/Person.h \
    DRCClient.h \
    drc_shared/models/Intake.h \
    gui/fruitnameform.h \
    drc_shared/models/DRCModels.h \
    gui/intakeform.h \
    gui/mainmenutabwidget.h \
    gui/particapants.h

FORMS    += \
    DRCClient.ui \
    gui/fruitnameform.ui \
    gui/intakeform.ui \
    gui/mainmenutabwidget.ui \
    gui/particapants.ui

CONFIG += c++11
