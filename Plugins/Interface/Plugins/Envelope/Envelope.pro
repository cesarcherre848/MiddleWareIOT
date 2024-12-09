TEMPLATE = lib
CONFIG += plugin c++17
TARGET = Envelope
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += envelope.h \
    Models/EVConf.h \
    #Constants/flowMaps.h \
    # Models/UCConf.h #\
    Utils/TimeDomain.h

SOURCES += envelope.cpp

include("Third/Third.pri")

INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildGCC11/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../





