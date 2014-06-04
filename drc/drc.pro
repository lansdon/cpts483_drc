#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T19:38:12
#
#-------------------------------------------------

QT      += core gui
QT	+= sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drc
TEMPLATE = app

INCLUDEPATH += bl/ \
    db/ \
    drc_shared/ \
    drc_shared/mediator/ \
    drc_shared/models/ \
    gui/

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
    gui/particapants.cpp \
    bl/fruitnameprocessor.cpp \
    bl/intakeformprocessor.cpp \
    gui/loginform.cpp \
    bl/Crypto/SHA256_Crypto.cpp \
    drc_shared/mediator/asyncmediatorworker.cpp \
    gui/partydetailsform.cpp \
    gui/queryform.cpp \
    drc_shared/models/Fruit.cpp \
<<<<<<< HEAD
    gui/contactrecordview.cpp \
    gui/contactrecorddataview.cpp
=======
    bl/userloginprocessor.cpp \
    drc_shared/models/User.cpp
>>>>>>> b5134fdae3bfd5ab5737e71a1f8fea3a946211c9

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
    gui/particapants.h \
    bl/fruitnameprocessor.h \
    bl/intakeformprocessor.h \
    db/Filter.h \
    db/FilterTypes.h \
    drc_shared/models/Fruit.h \
    drc_shared/models/User.h \
    drc_shared/models/UserType.h \
    db/sqlite3.h \
    bl/Processor.h \
    bl/userloginprocessor.h \
    bl/Crypto/SHA256_Crypto.h \
    gui/loginform.h \
    bl/Crypto/SHA256_Crypto.h \
    drc_shared/mediator/asyncmediatorworker.h \
    gui/partydetailsform.h \
    gui/queryform.h \
<<<<<<< HEAD
    gui/contactrecordview.h \
    gui/contactrecorddataview.h
=======
    drc_shared/models/DBBaseObject.h
>>>>>>> b5134fdae3bfd5ab5737e71a1f8fea3a946211c9

FORMS    += \
    DRCClient.ui \
    gui/fruitnameform.ui \
    gui/intakeform.ui \
    gui/particapants.ui \
    gui/loginform.ui \
    gui/partydetailsform.ui \
    gui/queryform.ui \
    gui/contactrecordview.ui \
    gui/contactrecorddataview.ui


CONFIG += c++11

OTHER_FILES += \
    
