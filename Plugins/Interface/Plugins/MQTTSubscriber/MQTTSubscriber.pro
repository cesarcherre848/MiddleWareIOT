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



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildGCC11/debug/ -lPluginInterface




#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
#LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../BuildMingw8164/ -lPluginInterface




INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/release/ -lMQTTCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/debug/ -lMQTTCommLib


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildGCC11/release/MQTTCommLib/ -lMQTTCommLib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Communication/MQTTComm/BuildGCC11/debug/MQTTCommLib/ -lMQTTCommLib


INCLUDEPATH += $$PWD/../../../../Communication/MQTTComm/MQTTCommLib
DEPENDPATH += $$PWD/../../../../Communication/MQTTComm/MQTTCommLib




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildMingw8164/debug/ -lMQTTParser


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildGCC11/release/ -lMQTTParser
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/MQTTParser/BuildGCC11/debug/ -lMQTTParser


INCLUDEPATH += $$PWD/../../../../DataParsers/MQTTParser
DEPENDPATH += $$PWD/../../../../DataParsers/MQTTParser


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/release/ -lPayloadErbessdLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/debug/ -lPayloadErbessdLib

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildGCC11/release/PayloadErbessdLib/ -lPayloadErbessdLib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadErbessd/BuildGCC11/debug/PayloadErbessdLib/ -lPayloadErbessdLib


INCLUDEPATH += $$PWD/../../../../DataParsers/PayloadErbessd/PayloadErbessdLib
DEPENDPATH += $$PWD/../../../../DataParsers/PayloadErbessd/PayloadErbessdLib






INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib








win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadMilesight/BuildMingw8164/PayloadMilesightLib/release/ -lPayloadMilesightLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadMilesight/BuildMingw8164/PayloadMilesightLib/debug/ -lPayloadMilesightLib

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadMilesight/BuildGCC11/release/PayloadMilesightLib/ -lPayloadMilesightLib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../DataParsers/PayloadMilesight/BuildGCC11/debug/PayloadMilesightLib/ -lPayloadMilesightLib


INCLUDEPATH += $$PWD/../../../../DataParsers/PayloadMilesight/PayloadMilesightLib
DEPENDPATH += $$PWD/../../../../DataParsers/PayloadMilesight/PayloadMilesightLib
