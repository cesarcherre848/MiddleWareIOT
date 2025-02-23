QT += testlib
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_dataparse.cpp


INCLUDEPATH += \
    $$PWD \
    ../PayloadMilesight



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildMingw8164/PayloadMilesightLib/debug/ -lPayloadMilesightlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildMingw8164/PayloadMilesightLib/debug/ -lPayloadMilesightlib


#LIBS += -L$$PWD/../BuildMingw8164/PayloadErbessdLib/debug/ -lpayloaderbessdlib


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildGCC11/release/PayloadMilesightLib/ -lPayloadMilesightlib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildGCC11/debug/PayloadMilesightLib/ -lPayloadMilesightlib



INCLUDEPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../Manager/DataManager/DataManagerLib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/debug/ -lMQTTParser


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/release/ -lMQTTParser
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/debug/ -lMQTTParser


INCLUDEPATH += $$PWD/../../MQTTParser
DEPENDPATH += $$PWD/../../MQTTParser



