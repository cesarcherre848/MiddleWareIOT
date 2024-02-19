#include "processor.h"
#include "QCoreApplication"
#include "QDir"
#include "QPluginLoader"
//#include "../Interface/plugininterface.h"
#include "QList"
#include "QUuid"


Processor::Processor(QSettings &_settings) : BaseService{_settings}
{
    initConfig();



#ifdef QT_DEBUG

    addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/UnitConverter/BuildMingw8164/debug");
    addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/FFTAnalysis/BuildMingw8164/debug");
    addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/BasicStatistics/BuildMingw8164/debug");


#else \
    // Código para compilación en modo Release
#endif


    loadConfig();


    loadPluginIntances();
    qDebug() << "Operations Instances:";
    printOperationsInstances();

    mainTimeout();
}

Processor::~Processor()
{

}




void Processor::execute()
{

    int maxQueuesProcessItems_ = 10;
    int itemsToProcess = qMin(sizeDataQueue(), maxQueuesProcessItems_);
    for (int i = 0; i < itemsToProcess; ++i) {
        Signal currentData = dequeueDataQueue();


        insertDatatoOperation(currentData);
        emit newProcessData(currentData);
    }

    if(itemsToProcess > 0){
        executeAllOperations();
    }

}

void Processor::initConfig()
{
    const QSettings& settings = getSettings();
    double interval = settings.value("Processor/Interval", 1.).toDouble();
    dirConfig = dirRel + settings.value("Processor/DirConfig", "/Config/Process").toString();
    setInterval(interval);
}



