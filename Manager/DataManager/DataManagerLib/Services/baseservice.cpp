#include "baseservice.h"
#include "QDir"
#include "QPluginLoader"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

BaseService::BaseService(QSettings &_settings) : settings(_settings){
    timer = new QTimer(this);
}

BaseService::~BaseService()
{

    if(timer){
        timer->stop();
        timer->deleteLater();
    }

}

void BaseService::loadPluginIntances()
{

    for (int i = 0; i < operations.size(); ++i) {
        Operation operation = operations[i];
        std::shared_ptr<PluginInterface> pluginInterface = getPluginInterface(operation);
        if(pluginInterface){
            connect(pluginInterface.get(), SIGNAL(processedData(const Signal&)), this, SLOT(reciveProcessedData(const Signal&)));
            operationsInstances.append(pluginInterface);
        }
    }


}

std::shared_ptr<PluginInterface>BaseService::getPluginInterface(Operation operation)
{
    QStringList fullFilenamePlugins;
    QString dirName;
    foreach (dirName, directoryPlugins) {
        QDir directorioPlugins(dirName);
        QStringList filenames = directorioPlugins.entryList(QDir::Files);
        for (int i = 0; i < filenames.size(); ++i) {
            filenames[i] = dirName + "/" + filenames[i];
        }


        fullFilenamePlugins << filenames;
    }


    foreach(const QString& file, fullFilenamePlugins) {

        QPluginLoader loader(file);

        if (loader.load()) {
            QObject* pluginInstance = loader.instance();

            if (pluginInstance) {
                PluginInterface *plugin = qobject_cast<PluginInterface*>(pluginInstance);

                if (plugin) {



                    if(plugin->getName() == operation.name){

                        std::shared_ptr<PluginInterface> instance(plugin->newInstance());
                        instance->setSetup(operation.setup);
                        instance->setAsginedSignals(operation.assignedSignalName);
                        if(!asignedComponents.isEmpty()){
                            instance->setAsignedComponents(asignedComponents);
                        }
                        return instance;
                    }
                    else{
                        //qDebug() << pluginInstance;
                        //pluginInstance->deleteLater();
                        delete pluginInstance;
                    }
                } else {
                    qWarning() << loader.errorString();
                }
            }
            else{
                qWarning() << loader.errorString();
            }
        }
    }
    return nullptr;
}

void BaseService::jsonByteArrayToOperation(QByteArray byteArray)
{

    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray);
    if (!jsonDoc.isArray()) {
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    for (int i = 0; i < jsonArray.count(); ++i) {
        QJsonObject object = jsonArray.at(i).toObject();
        QJsonArray assChsArray = object["Assigned Channels"].toArray();
        QJsonObject setupObj = object["Setup"].toObject();
        QString nameOp = object["Plugin"].toString();
        QStringList assChsOp;
        QMap<QString, QVariant> setupOp;
        for (const QJsonValue& assChArray : assChsArray) {
            assChsOp.append(assChArray.toString());
        }
        for (auto it = setupObj.begin(); it != setupObj.end(); ++it) {
            setupOp.insert(it.key(), it.value().toVariant());

        }
        if(!nameOp.isEmpty() || !assChsOp.empty()){
            Operation operation;
            operation.name = nameOp;
            operation.assignedSignalName = assChsOp;
            operation.setup = setupOp;
            operations << operation;
        }
    }

}

void BaseService::setAsignedComponents(const QMap<QString, AssignedComponent> &newAsignedComponents)
{
    asignedComponents = newAsignedComponents;
}

void BaseService::loadConfig()
{
    QDir dirBase(dirConfig);
    QString fullPathConfig;
    QStringList files = dirBase.entryList({"*.json"},QDir::Files);
    for (const QString& file : files) {
        if (file == "config.json") {
            fullPathConfig = dirBase.filePath(file);
            break;
        }
    }

    if(fullPathConfig.isEmpty()){
        return;
    }

    QFile fileConfig(fullPathConfig);


    QByteArray jsonData;
    if (fileConfig.open(QIODevice::ReadOnly | QIODevice::Text)) {
        jsonData = fileConfig.readAll();
        fileConfig.close();
    }

    if(jsonData.isEmpty()){
        return;
    }

    jsonByteArrayToOperation(jsonData);
}

void BaseService::mainTimeout()
{
    connect(timer, &QTimer::timeout, this, &BaseService::execute);
    timer->start((int)interval*1000);


}

void BaseService::setInterval(float newInterval)
{
    interval = newInterval;
}

void BaseService::addDirectoryPlugins(QString dir)
{
    directoryPlugins << dir;
}

void BaseService::printOperationsInstances()
{

    foreach(std::shared_ptr<PluginInterface> operationInstance, operationsInstances){
        qDebug() << operationInstance.get();
    }

}

void BaseService::enqueueDataQueue(const Signal &data)
{
    dataQueue.enqueue(data);
}

Signal BaseService::dequeueDataQueue()
{
    return dataQueue.dequeue();
}

void BaseService::insertData(const Signal &data)
{
    mutex.lock();
    enqueueDataQueue(data);
    mutex.unlock();
}

int BaseService::sizeDataQueue()
{
    return dataQueue.size();
}

QSettings &BaseService::getSettings() const
{
    return settings;
}




void BaseService::executeAllOperations()
{
    for (std::shared_ptr<PluginInterface> instance : operationsInstances) {
        if(instance){
            instance->execute();
        }

    }
}

void BaseService::insertDatatoOperation(const Signal &data)
{
    for (std::shared_ptr<PluginInterface> instance : operationsInstances) {
        if(instance){
            instance->insertData(data);
        }
    }
}

void BaseService::reciveProcessedData(const Signal & data)
{
    emit returnDataToInputQueue(data);
}
