#include "inputflow.h"
#include <QUuid>

InputFlow::InputFlow(QQueue<Signal>& inputDataQueue, QSettings &_settings)

   : inputDataQueue_(inputDataQueue), BaseService{_settings}
{


    initConfig();
#ifdef QT_DEBUG


    addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/MQTTSubscriber/BuildMingw8164/debug");

//dirConfig = dirRel + "/Config/Output";

#else \
    // Código para compilación en modo Release
#endif

    loadConfig();


    loadPluginIntances();

    qDebug() << "Operations Input Instances:";
    printOperationsInstances();

    verifySizeInputQueue();
    mainTimeout();
}

InputFlow::~InputFlow()
{
    if(sizeCheckTimer){
        delete sizeCheckTimer;
    }

    if(timer){
        delete timer;
    }
}

void InputFlow::insertData(const Signal & data)
{
    mutex.lock();
    inputDataQueue_.enqueue(data);
    mutex.unlock();

    //emit newInputData(data);
}

void InputFlow::verifySizeInputQueue()
{
    sizeCheckTimer = new QTimer(this);
    QObject::connect(sizeCheckTimer, &QTimer::timeout, this, [=]() {
        if (this->inputDataQueue_.size() > limitSize) { // Verificar si el tamaño de la cola supera el límite
            qWarning() << QString("La cola ha superado el límite de tamaño. Eliminando (%1) elementos...").arg(inputDataQueue_.size());
            this->inputDataQueue_.clear();
        }
    });
}

void InputFlow::mainTimeout()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        int items = inputDataQueue_.size();
        for (int i = 0; i < items; ++i) {
            mutex.lock();
            Signal currentSignal = inputDataQueue_.dequeue();
            mutex.unlock();
            emit newInputData(currentSignal);
        }
    });
    timer->start(1000);
}

void InputFlow::initConfig()
{
    const QSettings& settings = getSettings();
    dirConfig = dirRel + settings.value("Input/DirConfig", "/Config/Input").toString();
}

void InputFlow::setLimitSize(int newLimitSize)
{
    limitSize = newLimitSize;
}

void InputFlow::setMsVerify(int newMsVerify)
{
    msVerify = newMsVerify;
}

void InputFlow::setCleanTimeout(bool newCleanTimeout)
{
    cleanTimeout = newCleanTimeout;
    sizeCheckTimer->stop();
    sizeCheckTimer->setInterval(msVerify);
    if(newCleanTimeout){
       sizeCheckTimer->start();
    }
    else{
       sizeCheckTimer->stop();
    }
}
