#include "app.h"
#include "QDebug"
#ifdef Q_OS_WIN
#include <windows.h>
#endif


#ifdef Q_OS_WIN
static BOOL WINAPI consoleCtrlHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        QCoreApplication::exit();
        return TRUE;
    }
    return FALSE;
}
#endif

App::App(int argc, char **argv) :
    QCoreApplication(argc, argv)
{
    connect(this, &QCoreApplication::aboutToQuit, this, &App::cleanupBeforeExit);
    setupConsoleCtrlHandler();
}

void App::cleanupBeforeExit()
{
    qWarning() << "Exit requesting ..";
}

void App::setupConsoleCtrlHandler()
{
#ifdef Q_OS_WIN
    SetConsoleCtrlHandler(consoleCtrlHandler, TRUE);
#endif
}
