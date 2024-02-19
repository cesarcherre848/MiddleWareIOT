QT -= gui

QT += core network mqtt


TEMPLATE = lib
DEFINES += MQTTCOMM_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mqttcomm.cpp

HEADERS += \
    Constants/textMaps.h \
    MQTTComm_global.h \
    mqttcomm.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
