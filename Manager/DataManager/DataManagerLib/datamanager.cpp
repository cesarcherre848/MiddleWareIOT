#include "datamanager.h"
#include "QDebug"



DataManager::DataManager(QSettings& _settings)
    :settings(_settings)
{

    idNodes = {"189301637", "189301605"};
    InitDB();
    getDataFromDB();



    qDebug() << "Hola mundo DataManager";

    inputFlow = new InputFlow(inputDataQueue, settings);
    inputFlow->setCleanTimeout(true);
    inputFlow->setParent(this);



    processor = new Processor(settings);



    connect(inputFlow, &InputFlow::newInputData, processor, &Processor::insertData);
    connect(inputFlow, &InputFlow::returnDataToInputQueue, inputFlow, &InputFlow::insertData);

    // retorno a la cola de entrada de los procesados
    connect(processor, &Processor::returnDataToInputQueue, inputFlow, &InputFlow::insertData);


    outputFlow = new OutputFlow(asignedComponents, settings);

    // conectar el processor con el salida
    connect(processor, &Processor::newProcessData, outputFlow, &OutputFlow::insertData);



}

DataManager::~DataManager()
{
    if(inputFlow){
        inputFlow->deleteLater();
    }
    if(processor){
        processor->deleteLater();
    }
    if(outputFlow){
        outputFlow->deleteLater();
    }
}

void DataManager::insertInputDataQueue(const Signal &signal)
{
    if(!inputFlow){
        return;
    }

    inputFlow->insertData(signal);
    /*
    mutex.lock();
    inputDataQueue.enqueue(signal);
    mutex.unlock();

    qDebug() << "insert to queue";
    */
}

void DataManager::setProcessInterval(int newProcessInterval)
{
    if(newProcessInterval < 100){
        processInterval = 100;
        return;
    }
    processInterval = newProcessInterval;
}

void DataManager::setMaxQueuesProcessItems(int newMaxQueuesProcessItems)
{
    if(newMaxQueuesProcessItems > 300){
        maxQueuesProcessItems = 300;
        return;
    }
    maxQueuesProcessItems = newMaxQueuesProcessItems;
}

void DataManager::InitDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("146.190.122.149"); // Solo el nombre del host o la IP, sin el número de puerto
    db.setPort(5432);
    db.setDatabaseName("Empresa1");
    db.setUserName("root");
    db.setPassword("Mc05071995..");
    db.open();
}

void DataManager::getDataFromDB()
{
    QSqlQuery query;
    query.prepare("SELECT \"Id_Node\", \"Id_Component\", \"ChannelKey\" FROM \"SensorComponent\" AS sc "
                  "where sc.\"Id_Node\" IN (" + formatIdNodes() + ")");
    //query.bindValue(":IdNodes", formatIdNodes());





    if (!query.exec()) {
        qDebug() << "Error al ejecutar la consulta:" << query.lastError().text();
        return;
        db.close();
    }

    while (query.next()) {
        QString idNode = query.value(0).toString();
        QString idComponent = query.value(1).toString();
        QByteArray jsonByteArray = query.value(2).toByteArray();

        AssignedComponent value;
        value.id = idComponent;
        value.channel = byteArrayJsonToChannels(jsonByteArray);
        asignedComponents.insert(idNode,value);
    }

    db.close();
}

QMap<QString, QString> DataManager::byteArrayJsonToChannels(QByteArray bytearray)
{
    QMap<QString, QString> output;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytearray);
    if (!jsonDoc.isObject()){
        return {};
    }
    QJsonObject jsonObj = jsonDoc.object();
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        output.insert(it.key(), it.value().toString());

    }

    return output;
}

QString DataManager::formatIdNodes()
{
    QStringList output;

    for (const QString &item : idNodes) {
        output.append("'" + item + "'");
    }
    return output.join(", ");
}

