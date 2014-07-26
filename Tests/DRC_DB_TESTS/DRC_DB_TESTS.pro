#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T21:20:02
#
#-------------------------------------------------

QT       += sql testlib
QT       += widgets
QT       -= gui
QT       += printsupport

TARGET = tst_drc_db_tests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app

INCLUDEPATH += ../../drc/drc_shared/models/ \
    ../../drc/db/ \
    ../../drc/gui/ \
    ../../drc/drc_shared/mediator \
    ../../drc/bl/ \
    ../../drc/drc_shared/ \
    ../../drc


SOURCES += tst_drc_db_tests.cpp \
    ../../drc/db/drcdb.cpp \
    ../../drc/drc_shared/models/Person.cpp \
    ../../drc/drc_shared/models/CurrentUser.cpp \
    ../../drc/drc_shared/models/mediationprocess.cpp \
    ../../drc/drc_shared/models/mediationsession.cpp \
    ../../drc/drc_shared/models/party.cpp \
    ../../drc/drc_shared/drctypes.cpp \
    ../../drc/drc_shared/mediator/Mediator.cpp \
    ../../drc/drc_shared/models/User.cpp \
    ../../drc/bl/Crypto/SHA256_Crypto.cpp \
    ../../drc/drc_shared/models/clientsessiondata.cpp \
    ../../drc/drc_shared/models/reswareport.cpp \
    ../../drc/drc_shared/models/mediationevaluation.cpp \
    ../../drc/drc_shared/models/monthlyreport.cpp \
    ../../drc/drc_shared/models/Note.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../drc/db/drcdb.h \
    ../../drc/drc_shared/models/DBBaseObject.h \
    ../../drc/drc_shared/models/Person.h \
    ../../drc/db/Filter.h \
    ../../drc/drc_shared/models/mediationprocess.h \
    ../../drc/drc_shared/models/mediationsession.h \
    ../../drc/drc_shared/models/party.h \
    ../../drc/drc_shared/drctypes.h \
    ../../drc/drc_shared/mediator/Mediator.h \
    ../../drc/drc_shared/mediator/MediatorArg.h \
    ../../drc/drc_shared/mediator/MediatorKeys.h \
    ../../drc/drc_shared/models/User.h \
    ../../drc/drc_shared/models/DRCModels.h \
    ../../drc/bl/Crypto/SHA256_Crypto.h \
    ../../drc/drc_shared/models/clientsessiondata.h \
    ../../drc/drc_shared/models/reswareport.h \
    ../../drc/drc_shared/models/mediationevaluation.h \
    ../../drc/drc_shared/models/monthlyreport.h \
    ../../drc/drc_shared/models/Note.h
