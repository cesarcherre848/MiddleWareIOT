TEMPLATE = lib
CONFIG += plugin c++17
TARGET = MQTTSubscriber
INCLUDEPATH += ./

QT += core
QT += network mqtt

# Archivos fuente
HEADERS += mqttsubscriber.h \
    Constants/textMaps.h \
    Models/MSConf.h \
    Utils/parserthread.h

SOURCES += mqttsubscriber.cpp \
    Utils/parserthread.cpp

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




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildMingw8164/debug/ -lMQTTParser

INCLUDEPATH += $$PWD/../../../../DataParsers/MQTTParser
DEPENDPATH += $$PWD/../../../../DataParsers/MQTTParser

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/release/ -lPayloadErbessdLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/debug/ -lPayloadErbessdLib

INCLUDEPATH += $$PWD/../../../../DataParsers/PayloadErbessd/PayloadErbessdLib
DEPENDPATH += $$PWD/../../../../DataParsers/PayloadErbessd/PayloadErbessdLib


INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
