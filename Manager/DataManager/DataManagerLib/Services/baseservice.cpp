#include "baseservice.h"
#include "QDir"
#include "QPluginLoader"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

BaseService::BaseService(QSettings &_settings) : settings(_settings){}

BaseService::~BaseService()
{
    if(timer){
        delete timer;
    }

    for (PluginInterface* obj : operationsInstances) {
        delete obj;
    }
    operationsInstances.clear();

}

void BaseService::loadPluginIntances()
{

    for (int i = 0; i < operations.size(); ++i) {
        Operation operation = operations[i];
        PluginInterface * pluginInterface = getPluginInterface(operation);
        if(pluginInterface){
            connect(pluginInterface, SIGNAL(processedData(const Signal&)), this, SLOT(reciveProcessedData(const Signal&)));
            operationsInstances.append(pluginInterface);
        }
    }


}

PluginInterface *BaseService::getPluginInterface(Operation operation)
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

                        std::unique_ptr<PluginInterface> instance(plugin->newInstance());
                        instance->setSetup(operation.setup);
                        instance->setAsginedSignals(operation.assignedSignalName);
                        if(!asignedComponents.isEmpty()){
                            instance->setAsignedComponents(asignedComponents);
                        }
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
    timer = new QTimer(this);
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
    qDebug() << operationsInstances;
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
    for (PluginInterface* instance : operationsInstances) {
        if(instance){
            instance->execute();
        }

    }
}

void BaseService::insertDatatoOperation(const Signal &data)
{
    for (PluginInterface* instance : operationsInstances) {
        if(instance){
            instance->insertData(data);
        }
    }
}

void BaseService::reciveProcessedData(const Signal & data)
{
    emit returnDataToInputQueue(data);
}
