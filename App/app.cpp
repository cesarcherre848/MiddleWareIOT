#include "app.h"
#include "QDebug"
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <csignal>
#include <unistd.h>
#endif


#ifdef _WIN32
static BOOL WINAPI consoleCtrlHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        QCoreApplication::quit();
        return TRUE;
    }
    return FALSE;
}
#elif __linux__
static void handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        QCoreApplication::quit();
    }
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
    emit exitRequest();
    qWarning() << "Exit requesting ...";
}

void App::setupConsoleCtrlHandler()
{
#ifdef _WIN32
    SetConsoleCtrlHandler(consoleCtrlHandler, TRUE);
#elif __linux__
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);
#endif
}
