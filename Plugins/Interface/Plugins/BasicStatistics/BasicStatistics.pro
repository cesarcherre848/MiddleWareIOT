TEMPLATE = lib
CONFIG += plugin c++17
TARGET = BasicStatistics
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += basicstatistics.h \
    Constants/textMaps.h \
    Models/BSConf.h \
    Utils/TimeDomain.h


SOURCES += basicstatistics.cpp

#include("Third/Third.pri")


INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildGCC11/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../






