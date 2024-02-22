#include "app.h"
#include "QDebug"

#ifdef Q_OS_WIN
BOOL WINAPI consoleCtrlHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        qWarning() << "Start clossing request";
        QCoreApplication::exit();
        return TRUE;
    }
    return FALSE;
}
#endif

App::App(int &argc, char **argv):
    QCoreApplication(argc, argv)
{
    connect(this, &QCoreApplication::aboutToQuit, this, &App::cleanupBeforeExit);

#ifdef Q_OS_WIN

    SetConsoleCtrlHandler(consoleCtrlHandler, TRUE);
#endif
}

void App::cleanupBeforeExit()
{
    qDebug() << "Se realiza la limpieza";
}
