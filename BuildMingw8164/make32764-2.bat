@echo off
cd App\ && ( if not exist Makefile C:\Qt\6.2.0\mingw81_64\bin\qmake.exe -o Makefile "D:\Proyectos\Health Vibration Monitoring\MiddleWareIOT\App\App.pro" -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" ) && C:/Qt/Tools/mingw810_64/bin/mingw32-make -f Makefile 
