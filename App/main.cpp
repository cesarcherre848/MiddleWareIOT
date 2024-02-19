#include <QCoreApplication>
#include "QDebug"
#include "Controllers/maincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    MainController m;

    qDebug() << "Hola mundo";

    return a.exec();
}
