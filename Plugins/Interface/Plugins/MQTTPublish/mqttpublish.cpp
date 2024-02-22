#include "mqttpublish.h"
#include "QDebug"
#include "mqttpublish.h"
#include <QJsonObject>
#include <QJsonDocument>
//#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *MQTTPublish::newInstance()
{
    return new MQTTPublish();
}

MQTTPublish::MQTTPublish()
{
    comm = new MQTTComm(this);
}

MQTTPublish::~MQTTPublish()
{
    if(comm){
        comm->deleteLater();
    }
}

void MQTTPublish::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getConf();
    initMQTTCommunication();

}

void MQTTPublish::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;


}

QString MQTTPublish::getName() const
{
    return "MQTTPublish";
}

void MQTTPublish::execute()
{

    if(!comm){
        return;
    }


    if(inputDataQueue.size() <  1){
        return;
    }



    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        Signal currentData = inputDataQueue.dequeue();
        applyComponentSignal(currentData);
        QByteArray message = parseValuePayload(currentData);
        publishMultipleTopics(message, conf.topics);
    } 
    inputDataQueue.clear();
}


void MQTTPublish::insertData(const Signal & data)
{

    if(asginedSignals.contains(data.name)){
        if(data.type != Type::value){
            return;
        }

        inputDataQueue.enqueue(data);
    }
}

void MQTTPublish::setAsignedComponents(const QMap<QString, AssignedComponent> & newAsignedComponents)
{
    asignedComponents = newAsignedComponents;
}




void MQTTPublish::getConf()
{
    if(setup.contains("hostname")){
        QString hostname = setup["hostname"].toString();
        conf.hostname = hostname;
    }
    if(setup.contains("port")){
        int port = setup["port"].toInt();
        conf.port = port;
    }
    if(setup.contains("topics")){
        QStringList topics = setup["topics"].toStringList();
        conf.topics = topics;
    }

}

void MQTTPublish::initMQTTCommunication()
{
    if(conf.port == 0){
        return;
    }

    if(conf.hostname.isEmpty()){
        return;
    }


    comm->setHostName(conf.hostname);
    comm->setPort(conf.port);
    connect(comm, &MQTTComm::updateStatusConnection, this, [=](QString msg){
        qWarning() << QString("%1 %2").arg(getName()).arg("Connections Status") << msg;
    });
    comm->connect();
}

QByteArray MQTTPublish::parseValuePayload(const Signal &data)
{
    QJsonObject jsonObject;
    jsonObject["measurement"] = data.name;
    jsonObject["value"] = data.value;
    jsonObject["unit"] = data.unit;
    jsonObject["timestamp"] = data.timestamp.toSecsSinceEpoch();
    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonByteArray = jsonDocument.toJson();

    return jsonByteArray;
}

void MQTTPublish::applyComponentSignal(Signal &signal)
{



    QString idNode = signal.idNode;
    QString& name = signal.name;
    QString channel = signal.channel;

    if(asignedComponents.contains(idNode)){
        QString idComponent = asignedComponents[idNode].id;
        QMap<QString, QString> channelMap = asignedComponents[idNode].channel;
        name = name.replace(idNode, idComponent);
        if(channelMap.contains(channel)){
            QString newChannel = channelMap[channel];
            name = name.replace(channel, newChannel);
        }
    }
}

void MQTTPublish::publishMultipleTopics(QByteArray message, QStringList topics)
{
    foreach (QString topic, topics) {
        comm->publishPayload(message, topic);
    }
}

