TEMPLATE = lib
CONFIG += plugin c++17
TARGET = FFTAnalysis
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += fftanalysis.h \
    Constants/textMaps.h \
    Constants/valuesMaps.h \
    Models/FFTConf.h \
    Models/ScalarsConf.h \
    Models/Units.h \
    Utils/FreqDomain.h \
    Utils/TimeDomain.h \
    Utils/UnitsConvert.h

SOURCES += fftanalysis.cpp

include("Third/Third.pri")

INCLUDEPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../../Manager/DataManager/DataManagerLib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/release/ -lPluginInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildMingw8164/debug/ -lPluginInterface

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BuildGCC11/debug/ -lPluginInterface

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

