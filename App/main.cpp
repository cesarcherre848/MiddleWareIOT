#include <QCoreApplication>
#include "QDebug"
#include "Controllers/maincontroller.h"
#include "app.h"
#include "Services/EventDispatcher/eventdispatcher.h"


void mySlot() {
    qDebug() << "¡El temporizador de un solo disparo ha expirado!";
    QCoreApplication::quit();  // Cerrar la aplicación
}

int main(int argc, char *argv[])
{
    App a(argc, argv);


    EventDispatcher::instance();

    MainController m;

    qDebug() << "Hola mundo";
    //QTimer::singleShot(20000, &mySlot);


    return a.exec();
}
