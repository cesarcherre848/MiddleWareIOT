TEMPLATE = lib
CONFIG += plugin c++17
TARGET = MQTTSubscriber
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += mqttsubscriber.h \
    Models/MSConf.h

SOURCES += mqttsubscriber.cpp

include("Third/Third.pri")


INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../BuildMingw8164/ -lPluginInterface




INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../


#LIBS += -L$$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/BuildMingw8164/MQTTCommLib/debug/' -lMQTTCommLib

#INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'
#DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/release/ -lMQTTCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/debug/ -lMQTTCommLib

INCLUDEPATH += $$PWD/../../../../Communication/MQTTComm/MQTTCommLib
DEPENDPATH += $$PWD/../../../../Communication/MQTTComm/MQTTCommLib
