QT += testlib
QT -= gui
QT += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_dataflow.cpp

INCLUDEPATH += \
    $$PWD \
    ../DataManager



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/release/ -lDataManagerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildMingw8164/DataManagerLib/debug/ -lDataManagerLib

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../BuildGCC11/release/DataManagerLib/ -lDataManagerLib
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BuildGCC11/debug/DataManagerLib/ -lDataManagerLib


INCLUDEPATH += $$PWD/../DataManagerLib
DEPENDPATH += $$PWD/../DataManagerLib


unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildGCC11/release/ -lPluginInterface
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Plugins/Interface/BuildGCC11/debug/ -lPluginInterface


INCLUDEPATH += $$PWD/../../../Plugins/Interface
DEPENDPATH += $$PWD/../../../Plugins/Interface
