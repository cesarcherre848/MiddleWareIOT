QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_dataflow.cpp

INCLUDEPATH += \
    $$PWD \
    ../DataManager

LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/debug/ -lDataManagerLib


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/release/ -lDataManagerLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/debug/ -lDataManagerLib
#else:unix: LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/ -lDataManagerLib

INCLUDEPATH += $$PWD/../BuildMingw8164/DataManagerLib/debug
DEPENDPATH += $$PWD/../BuildMingw8164/DataManagerLib/debug
