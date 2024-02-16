TEMPLATE = lib
CONFIG += plugin c++17
TARGET = UnitConverter
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += unitconverter.h \
    Constants/flowMaps.h \
    Models/UCConf.h \
    Utils/TimeDomain.h

SOURCES += unitconverter.cpp

include("Third/Third.pri")

INCLUDEPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
DEPENDPATH += $$PWD/'../../../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface
#else:unix: LIBS += -L$$PWD/../../BuildMingw8164/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
