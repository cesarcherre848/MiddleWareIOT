QT += testlib
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_dataparse.cpp


INCLUDEPATH += \
    $$PWD \
    ../PayloadErbessd



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildMingw8164/PayloadErbessdLib/debug/ -lpayloaderbessdlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildMingw8164/PayloadErbessdLib/debug/ -lpayloaderbessdlib


#LIBS += -L$$PWD/../BuildMingw8164/PayloadErbessdLib/debug/ -lpayloaderbessdlib


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildGCC11/release/PayloadErbessdLib/ -lPayloadErbessdLib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildGCC11/debug/PayloadErbessdLib/ -lPayloadErbessdLib



INCLUDEPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../Manager/DataManager/DataManagerLib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/debug/ -lMQTTParser


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/release/ -lMQTTParser
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/debug/ -lMQTTParser


INCLUDEPATH += $$PWD/../../MQTTParser
DEPENDPATH += $$PWD/../../MQTTParser



