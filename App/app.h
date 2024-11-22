#ifndef APP_H
#define APP_H
#include "QCoreApplication"

class App : public QCoreApplication
{
    Q_OBJECT
public:
    App(int argc, char **argv);



public slots:
    void cleanupBeforeExit();


private:
    void setupConsoleCtrlHandler();

signals:

    void exitRequest();
};

#endif // APP_H
