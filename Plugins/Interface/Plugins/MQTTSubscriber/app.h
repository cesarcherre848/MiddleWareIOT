#ifndef APP_H
#define APP_H
#ifdef _WIN32
#include <windows.h>
#endif

#include <QCoreApplication>


class App  : public QCoreApplication
{
    Q_OBJECT
public:
    App(int &argc, char **argv);

public slots:
    void cleanupBeforeExit();

};

#endif // APP_H
