QT = core
QT += sql

CONFIG += c++17 cmdline



LIBS += -L$$PWD/../../'Dinamic Libraries/Comunications/MQTTComm/BuildMingw8164/MQTTCommLib/debug' -lmqttcommlib

INCLUDEPATH += $$PWD/'../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'
DEPENDPATH += $$PWD/'../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'


include("Third/Third.pri")


#INCLUDEPATH += $$PWD/'../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'
#DEPENDPATH += $$PWD/'../../Dinamic Libraries/Comunications/MQTTComm/MQTTCommLib'

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Controllers/maincontroller.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Controllers/maincontroller.h




#LIBS += -L$$PWD/'../../Dinamic Libraries/DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/debug/' -lPayloadErbessdLib

#INCLUDEPATH += $$PWD/'../../Dinamic Libraries/DataParsers/PayloadErbessd/PayloadErbessdLib'
#DEPENDPATH += $$PWD/'../../Dinamic Libraries/DataParsers/PayloadErbessd/PayloadErbessdLib'


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/release/ -lPayloadErbessdLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataParsers/PayloadErbessd/BuildMingw8164/PayloadErbessdLib/debug/ -lPayloadErbessdLib

INCLUDEPATH += $$PWD/../DataParsers/PayloadErbessd/PayloadErbessdLib
DEPENDPATH += $$PWD/../DataParsers/PayloadErbessd/PayloadErbessdLib




#LIBS += -L$$PWD/'../../Dinamic Libraries/Manager/DataManager/BuildMingw8164/DataManagerLib/debug/' -lDataManagerLib

#INCLUDEPATH += $$PWD/'../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
#DEPENDPATH += $$PWD/'../../Dinamic Libraries/Manager/DataManager/DataManagerLib'

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Manager/DataManager/BuildMingw8164/DataManagerLib/release/ -lDataManagerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Manager/DataManager/BuildMingw8164/DataManagerLib/debug/ -lDataManagerLib

INCLUDEPATH += $$PWD/../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../Manager/DataManager/DataManagerLib



LIBS += -L$$PWD/../Plugins/Interface/BuildMingw8164/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../Plugins/Interface
DEPENDPATH += $$PWD/../Plugins/Interface


