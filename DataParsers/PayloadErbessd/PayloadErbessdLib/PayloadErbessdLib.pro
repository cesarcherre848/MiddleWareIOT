QT -= gui

TEMPLATE = lib
DEFINES += PAYLOADERBESSD_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0






SOURCES += \
    payloaderbessd.cpp

HEADERS += \
    Constants/textMaps.h \
    Models/ErbessdData.h \
    PayloadErbessd_global.h \
    payloaderbessd.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../Manager/DataManager/DataManagerLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/debug/ -lMQTTParser

INCLUDEPATH += $$PWD/../../MQTTParser
DEPENDPATH += $$PWD/../../MQTTParser
