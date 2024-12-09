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


    const QSettings& settings = getSettings();
    QString dirPlugins = settings.value("Processor/Libs", "").toString();

    if(dirPlugins.isEmpty()){

#ifdef _WIN32
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/UnitConverter/BuildMingw8164/debug");
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/FFTAnalysis/BuildMingw8164/debug");
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/BasicStatistics/BuildMingw8164/debug");
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/Array2DStatistics/BuildMingw8164/debug");
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/Envelope/BuildMingw8164/debug");

#elif __linux__
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/BasicStatistics/BuildGCC11/debug");
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/UnitConverter/BuildGCC11/debug");
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/FFTAnalysis/BuildGCC11/debug");
#endif
    }

    else{
        addDirectoryPlugins(dirRel+dirPlugins);
    }

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


    int itemsToProcess = sizeDataQueue();
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



