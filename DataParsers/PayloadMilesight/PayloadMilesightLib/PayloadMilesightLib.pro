QT -= gui

TEMPLATE = lib
DEFINES += PAYLOADMILESIGHT_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0






SOURCES += \
    payloadmilesight.cpp

HEADERS += \
    Constants/textMaps.h \
    Models/MilesightData.h \
    PayloadMilesight_global.h \
    payloadmilesight.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../Manager/DataManager/DataManagerLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildMingw8164/debug/ -lMQTTParser


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/release/ -lMQTTParser
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../MQTTParser/BuildGCC11/debug/ -lMQTTParser



INCLUDEPATH += $$PWD/../../MQTTParser
DEPENDPATH += $$PWD/../../MQTTParser


