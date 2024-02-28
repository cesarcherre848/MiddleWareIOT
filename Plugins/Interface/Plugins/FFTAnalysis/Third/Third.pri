DEFINES += THRID_LIBS_STATIC

#FFTW3
win32 {
    INCLUDEPATH += $$PWD\FFTW3\include
}

win32: LIBS += $$PWD\FFTW3\lib\windows\libfftw3-3.dll
win32: LIBS += $$PWD\FFTW3\lib\windows\llibfftw3f-3.dll

unix:!macx: LIBS += -lfftw3


CONFIG += c++17
