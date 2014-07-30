#-------------------------------------------------
#
# Project created by QtCreator 2014-06-09T23:36:11
#
#-------------------------------------------------

QT       += testlib
QT       += printsupport

QT       -= gui

TARGET = tst_bltestsuit
CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../drc/bl/ \
    ../../drc/drc_shared/ \
    ../../drc/drc_shared/models/ \
    ../../drc/gui/ \
    ../../drc/drc_shared/mediator/ \
    ../../drc/ \
    ../../drc/drc_shared/models/

SOURCES += tst_bltestsuit.cpp \
    ../../drc/drc_shared/models/Person.cpp \
    ../../drc/drc_shared/models/mediationprocess.cpp \
    ../../drc/drc_shared/models/party.cpp \
    ../../drc/bl/stateupdate.cpp \
    ../../drc/drc_shared/drctypes.cpp \
    ../../drc/drc_shared/models/mediationsession.cpp \
    ../../drc/drc_shared/models/clientsessiondata.cpp \
    ../../drc/drc_shared/models/CurrentUser.cpp \
    ../../drc/drc_shared/models/mediationevaluation.cpp \
    ../../drc/drc_shared/models/monthlyreport.cpp \
    ../../drc/drc_shared/models/Note.cpp \
    ../../drc/drc_shared/models/reswareport.cpp \
    ../../drc/drc_shared/models/User.cpp \
    ../../drc/bl/Crypto/SHA256_Crypto.cpp \
    ../../drc/drc_shared/mpfilemaker.cpp \
    ../../drc/drc_shared/mediator/AsyncMediatorCall.cpp \
    ../../drc/drc_shared/mediator/asyncmediatorworker.cpp \
    ../../drc/drc_shared/mediator/Mediator.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../drc/drc_shared/models/clientsessiondata.h \
    ../../drc/drc_shared/models/CurrentUser.h \
    ../../drc/drc_shared/models/DBBaseObject.h \
    ../../drc/drc_shared/models/DRCModels.h \
    ../../drc/drc_shared/models/mediationevaluation.h \
    ../../drc/drc_shared/models/mediationprocess.h \
    ../../drc/drc_shared/models/mediationsession.h \
    ../../drc/drc_shared/models/monthlyreport.h \
    ../../drc/drc_shared/models/Note.h \
    ../../drc/drc_shared/models/party.h \
    ../../drc/drc_shared/models/Person.h \
    ../../drc/drc_shared/models/reswareport.h \
    ../../drc/drc_shared/models/User.h \
    ../../drc/drc_shared/mediator/MediatorKeys.h \
    ../../drc/drc_shared/CurrentUser.h \
    ../../drc/drc_shared/drctypes.h \
    ../../drc/drc_shared/mpfilemaker.h \
    ../../drc/drc_shared/reportrequest.h \
    ../../drc/drc_shared/mediator/AsyncMediatorCall.h \
    ../../drc/drc_shared/mediator/asyncmediatorworker.h \
    ../../drc/drc_shared/mediator/Mediator.h \
    ../../drc/drc_shared/mediator/MediatorArg.h
