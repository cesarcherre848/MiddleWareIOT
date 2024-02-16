QT -= gui
QT += sql


TEMPLATE = lib
DEFINES += DATAMANAGER_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Services/baseservice.cpp \
    Services/inputflow.cpp \
    Services/outputflow.cpp \
    Services/processor.cpp \
    datamanager.cpp

HEADERS += \
    DataManager_global.h \
    Models/Operation.h \
    Models/Signals.h \
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

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../MiddleWareIOT/Plugins/Interface/BuildMingw8164/release/ -lPluginInterface
LIBS += -L$$PWD/../../../../MiddleWareIOT/Plugins/Interface/BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../../../MiddleWareIOT/Plugins/Interface/BuildMingw8164/ -lPluginInterface

INCLUDEPATH += $$PWD/../../../../MiddleWareIOT/Plugins/Interface
DEPENDPATH += $$PWD/../../../../MiddleWareIOT/Plugins/Interface
