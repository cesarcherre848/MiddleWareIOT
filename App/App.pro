QT = core
QT += sql
QT += network mqtt


CONFIG += c++17 cmdline



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/release/ -lMQTTCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Communication/MQTTComm/BuildMingw8164/MQTTCommLib/debug/ -lMQTTCommLib

INCLUDEPATH += $$PWD/../Communication/MQTTComm/MQTTCommLib
DEPENDPATH += $$PWD/../Communication/MQTTComm/MQTTCommLib



include("Third/Third.pri")



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Controllers/maincontroller.cpp \
        Utils/globalresources.cpp \
        app.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Controllers/maincontroller.h \
    Utils/globalresources.h \
    app.h





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/release/ -lPayloadErbessdLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/debug/ -lPayloadErbessdLib

INCLUDEPATH += $$PWD/../DataParsers/PayloadErbessd/PayloadErbessdLib
DEPENDPATH += $$PWD/../DataParsers/PayloadErbessd/PayloadErbessdLib




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataParsers/MQTTParser/BuildMingw8164/release/ -lMQTTParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataParsers/MQTTParser/BuildMingw8164/debug/ -lMQTTParser

INCLUDEPATH += $$PWD/../DataParsers/MQTTParser
DEPENDPATH += $$PWD/../DataParsers/MQTTParser



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Manager/DataManager/BuildMingw8164/DataManagerLib/release/ -lDataManagerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Manager/DataManager/BuildMingw8164/DataManagerLib/debug/ -lDataManagerLib

INCLUDEPATH += $$PWD/../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../Manager/DataManager/DataManagerLib







win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Plugins/Interface/BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Plugins/Interface/BuildMingw8164/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../Plugins/Interface
DEPENDPATH += $$PWD/../Plugins/Interface
