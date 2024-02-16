TEMPLATE = lib
CONFIG += plugin c++17
TARGET = MQTTPublish
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += mqttpublish.h \
    Models/MPConf.h


SOURCES += mqttpublish.cpp

include("Third/Third.pri")


INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../BuildMingw8164/ -lPluginInterface




INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../


LIBS += -L$$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/BuildMingw8164/MQTTCommLib/debug/' -lMQTTCommLib

INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'
DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'
