QT -= gui
QT += sql
QT += core
QT += network

TEMPLATE = lib
DEFINES += DATAMANAGER_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Services/apirequest.cpp \
    Services/baseservice.cpp \
    Services/inputflow.cpp \
    Services/outputflow.cpp \
    Services/processor.cpp \
    datamanager.cpp

HEADERS += \
    DataManager_global.h \
    Models/Operation.h \
    Models/Signals.h \
    Services/apirequest.h \
    Services/baseservice.h \
    Services/inputflow.h \
    Services/outputflow.h \
    Services/processor.h \
    Utils/ServicesCommon.h \
    datamanager.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildGCC11/debug/ -lPluginInterface

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildMingw8164/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../../../Plugins/Interface
DEPENDPATH += $$PWD/../../../Plugins/Interface

