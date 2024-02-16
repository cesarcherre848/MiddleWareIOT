QT += testlib
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_dataparse.cpp


INCLUDEPATH += \
    $$PWD \
    ../PayloadErbessd

LIBS += -L$$PWD/../BuildMingw8164/PayloadErbessdLib/debug/ -lpayloaderbessdlib


INCLUDEPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
DEPENDPATH += $$PWD/../../../Manager/DataManager/DataManagerLib
