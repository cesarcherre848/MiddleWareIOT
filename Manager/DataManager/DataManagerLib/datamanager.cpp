#include "datamanager.h"
#include "QDebug"



DataManager::DataManager(QSettings& _settings)
    :settings(_settings)
{
    loadKnowIdNodes();
    InitDB();
    getDataFromDB();

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

    QString host = settings.value("Manager/DBHost", "").toString();
    int port = settings.value("Manager/DBPort", 0).toInt();
    QString name = settings.value("Manager/DBName", "").toString();
    QString user = settings.value("Manager/DBUser", "").toString();
    QString password = settings.value("Manager/DBPassword", "").toString();

    if( host.isEmpty() || name.isEmpty() || user.isEmpty() || password.isEmpty()){
        return;
    }

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(name);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qWarning() << "Error open DB Manager:" << db.lastError().text();
        return;
    }

    qInfo() << "Conection DB Maganer Succesfully";

}

void DataManager::getDataFromDB()
{
    if(!db.isOpen()){
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT \"Id_Node\", \"Id_Component\", \"ChannelKey\" FROM \"SensorComponent\" AS sc "
                  "where sc.\"Id_Node\" IN (" + formatIdNodes() + ")");


    if (!query.exec()) {
        qDebug() << "Error in query" << query.lastError().text();
        db.close();
        return;
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

    query.clear();
    QSqlDatabase::database().close();

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

void DataManager::loadKnowIdNodes()
{

    QString dirKnowIdNodes = settings.value("KnowIdNodes", "").toString();

    QString knownIdNodesFile = dirRel + dirKnowIdNodes;
    QFile file(knownIdNodesFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open knowIdNodes";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString idNode = in.readLine().trimmed();
        if(idNode.isEmpty())
        {
            continue;
        }
        idNodes << idNode;
    }

}

