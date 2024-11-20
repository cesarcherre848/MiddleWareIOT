TEMPLATE = lib
CONFIG += plugin c++17
TARGET = Array2DStatistics
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += array2dstatistics.h \
    Constants/textMaps.h \
    Models/A2DSConf.h \
    Utils/Array2DDomain.h \
    Utils/TimeDomain.h


SOURCES += array2dstatistics.cpp

#include("Third/Third.pri")


INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildGCC11/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../






