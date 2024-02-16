TEMPLATE = lib
CONFIG += plugin c++17
TARGET = PluginInterface
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += plugininterface.h
SOURCES += plugininterface.cpp


INCLUDEPATH += $$PWD/'../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'
DEPENDPATH += $$PWD/'../../../Dinamic Libraries/Manager/DataManager/DataManagerLib'



