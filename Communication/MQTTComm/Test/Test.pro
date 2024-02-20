QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_configurationtest.cpp


INCLUDEPATH += \
    $$PWD \
    ../MQTTComm


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildMingw8164/MQTTCommLib/release/ -lMQTTCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildMingw8164/MQTTCommLib/debug/ -lMQTTCommLib

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''
