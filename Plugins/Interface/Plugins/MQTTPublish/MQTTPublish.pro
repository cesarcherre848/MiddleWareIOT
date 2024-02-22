TEMPLATE = lib
CONFIG += plugin c++17
TARGET = MQTTPublish
INCLUDEPATH += ./

QT += core
QT += network mqtt

# Archivos fuente
HEADERS += mqttpublish.h \
    Models/MPConf.h


SOURCES += mqttpublish.cpp

include("Third/Third.pri")





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


INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
