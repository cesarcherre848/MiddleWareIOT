#include <QCoreApplication>
#include "QDebug"
#include "Controllers/maincontroller.h"
#include "app.h"

int main(int argc, char *argv[])
{
    App a(argc, argv);

    MainController m;

    qDebug() << "Hola mundo";

    return a.exec();
}
