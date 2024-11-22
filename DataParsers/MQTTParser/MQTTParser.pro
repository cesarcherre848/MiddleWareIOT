TEMPLATE = lib
CONFIG += plugin c++17
TARGET = MQTTParser
INCLUDEPATH += ./

QT += core

# Archivos fuente
HEADERS += mqttparser.h
SOURCES += mqttparser.cpp




INCLUDEPATH += $$PWD/../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../Manager/DataManager/DataManagerLib
