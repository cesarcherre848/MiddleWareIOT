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

#INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
#DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
#LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../BuildMingw8164/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

unix:!macx: LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface

#INCLUDEPATH += $$PWD/''
#DEPENDPATH += $$PWD/''


