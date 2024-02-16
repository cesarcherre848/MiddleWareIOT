#include "processor.h"
#include "QCoreApplication"
#include "QDir"
#include "QPluginLoader"
//#include "../Interface/plugininterface.h"
#include "QList"
#include "QUuid"

Processor::Processor(int& processInterval, int& maxQueuesProcessItems)
    : processInterval_(processInterval), maxQueuesProcessItems_(maxQueuesProcessItems)
{




#ifdef QT_DEBUG

    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/UnitConverter/BuildMingw8164/debug";
    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/FFTAnalysis/BuildMingw8164/debug";
    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/BasicStatistics/BuildMingw8164/debug";

    dirConfig = dirRel + "/Config/Process";
#else \
    // Código para compilación en modo Release
#endif


    loadConfig();

    //loadOperations();
    loadPluginIntances();
    //loadOperaitonInstances();

    qDebug() << "Operations Instances:" << operationsInstances;

    mainTimeout();
}

Processor::~Processor()
{
    for (PluginInterface* obj : operationsInstances) {
        delete obj;
    }
    operationsInstances.clear();
}


void Processor::startProcessing()
{
    processing = true;
    timer->start();
}

void Processor::stopProcessing()
{
    processing = false;
    timer->stop();
}

void Processor::process()
{



    if (!processing) {
        qDebug() << "Procesamiento detenido.";
        return;
    }


    int itemsToProcess = qMin(processDataQueue.size(), maxQueuesProcessItems_);
    for (int i = 0; i < itemsToProcess; ++i) {
        Signal currentData = processDataQueue.dequeue();


        insertDatatoOperation(currentData);
        emit newProcessData(currentData);
    }

    if(itemsToProcess > 0){
        executeAllOperations();
    }


    /*
    inputMutex_.lock();
    int itemsToProcess = qMin(inputDataQueue_.size(), maxQueuesProcessItems_);

    for (int i = 0; i < itemsToProcess; ++i) {
        Signal currentData = inputDataQueue_.dequeue();
        QString currentId = currentData.id;
        inputMutex_.unlock();
        if (!processedIds_.contains(currentId)) {

            //qDebug() << "Procesando dato con ID:" << currentId;

            // Marcar el ID como procesado


            insertDatatoOperation(currentData);


            inputMutex_.lock();
            processedIds_.insert(currentId);
            inputMutex_.unlock();
        }

        else {
            qDebug() << "Datos con ID" << currentId << "ya han sido procesados.";
        }

        inputMutex_.lock();
    }

    while (!inputDataQueue_.isEmpty() && processedIds_.contains(inputDataQueue_.front().id)) {
        processedIds_.remove(inputDataQueue_.dequeue().id);
    }

    inputMutex_.unlock();
    */


}

void Processor::loadOperations()
{
    Operation fft1;
    fft1.name = "FFTAnalysis";
    //fft1.assignedSignalName = {"189301635_Acceleration_ch0", "189301635_Acceleration_ch1", "189301635_Acceleration_ch2"};

    fft1.assignedSignalName = {
      "189301637_ERB_Accelerometer_ch0_UC",
      "189301637_ERB_Accelerometer_ch1_UC",
      "189301637_ERB_Accelerometer_ch2_UC",

      //"189301637_Accelerometer_ch0"
      //"189301637_Accelerometer_ch1",
      //"189301637_Accelerometer_ch2",
    };

    fft1.setup = {
        {"blockSize", QVariant(10192)},
        {"numAvg", QVariant(4)},
        {"avg", QVariant("Linear")},
        {"scale", QVariant("Linear")},
        {"ampFormat", QVariant("RMS")},
        {"window", QVariant("Hanning")},
        {"function", QVariant("FFT")},
        {"isDCFilter", QVariant(true)},
        {"fcDCFilter", QVariant(1.)},
        {"isFullRange", QVariant(true)},
        //{"customRanges", QVariant(QList<)}

    };





    Operation fft2;
    fft2.name = "FFTAnalysis";
    fft2.assignedSignalName = {"189301637_Acceleration_ch0", "189301637_Acceleration_ch1", "189301637_Acceleration_ch2"};
    fft2.setup = {
        {"blockSize", QVariant(2048)},
        {"numAvg", QVariant(800)},
        {"avg", QVariant("Linear")},
        {"scale", QVariant("Linear")},
        {"ampFormat", QVariant("Pk")},
        {"window", QVariant("Rectangular")},
        {"function", QVariant("FFT")},

    };

    Operation unitConverter1;
    unitConverter1.name = "UnitConverter";
    unitConverter1.assignedSignalName = {"189301637_ERB_Accelerometer_ch0", "189301637_ERB_Accelerometer_ch1", "189301637_ERB_Accelerometer_ch2"};


    Operation basicStats;
    basicStats.name = "BasicStatistics";
    basicStats.assignedSignalName = {
        "189301637_Accelerometer_ch0_UC",
        "189301637_Accelerometer_ch1_UC",
        "189301637_Accelerometer_ch2_UC",
        //"189301637_Accelerometer_ch0"
        //"189301637_Accelerometer_ch1",
        //"189301637_Accelerometer_ch2",
    };

    //operations << unitConverter1;
    //operations << fft1;
    //operations << basicStats;



    //operations << fft2;
}

/*
void Processor::loadOperaitonInstances()
{


#ifdef QT_DEBUG


    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/UnitConverter/BuildMingw8164/debug";
    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/FFTAnalysis/BuildMingw8164/debug";
    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/BasicStatistics/BuildMingw8164/debug";



#else \
    // Código para compilación en modo Release
#endif



    for (int i = 0; i < operations.size(); ++i) {
        Operation operation = operations[i];
        PluginInterface * pluginInterface = getPluginInterface(operation);
        if(pluginInterface){

            connect(pluginInterface, SIGNAL(processedData(const Signal&)), this, SLOT(reciveProcessedData(const Signal&)));

            operationsInstances.append(pluginInterface);
        }
    }

    qDebug() << operationsInstances;

}

PluginInterface* Processor::getPluginInterface(Operation operation)
{

    QStringList archivosPlugins;
    QString dirName;
    foreach (dirName, directoryPlugins) {
        QDir directorioPlugins(dirName);

        QStringList filenames = directorioPlugins.entryList(QDir::Files);

        for (int i = 0; i < filenames.size(); ++i) {
            filenames[i] = dirName + "/" + filenames[i];
        }
        archivosPlugins << filenames;
    }


    foreach(const QString& file, archivosPlugins) {

        QPluginLoader loader(file);

        if (loader.load()) {
            QObject* pluginInstance = loader.instance();


            if (pluginInstance) {
                PluginInterface *plugin = qobject_cast<PluginInterface*>(pluginInstance);

                if (plugin) {

                    if(plugin->getName() == operation.name){

                        std::unique_ptr<PluginInterface> instance(plugin->newInstance());
                        instance->setSetup(operation.setup);
                        instance->setAsginedSignals(operation.assignedSignalName);

                        return instance.release();
                    }
                    else{
                        pluginInstance->deleteLater();
                        pluginInstance = nullptr;
                    }
                } else {
                    qDebug() << "  No se pudo convertir a PluginInterface";
                }
            }
            loader.unload();
        }
    }

    return nullptr;
}


void Processor::executeAllOperations()
{
    for (PluginInterface* instance : operationsInstances) {
        if(instance){
            instance->execute();
        }

    }
}

void Processor::insertDatatoOperation(const Signal &data)
{

    for (PluginInterface* instance : operationsInstances) {
        if(instance){
           instance->insertData(data);
        }
    }
}

*/


void Processor::mainTimeout()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Processor::process);
    timer->start(1000);
}

void Processor::insertData(const Signal & data)
{


    mutex.lock();
    processDataQueue.enqueue(data);
    mutex.unlock();
}

/*
void Processor::reciveProcessedData(const Signal & data)
{
    emit returnDataToInputQueue(data);
}
*/
