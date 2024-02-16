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

MQTTPublish::~MQTTPublish()
{
    if(comm){
        comm->disconnect();
        delete comm;
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

        comm->publishPayload(message, "MiddleWareIOT");
        //computeOperation(currentData, outChannelQueue);
        //computeSingleFunction(currentData, singleChannelQueue);
    }


    /*
    int items = outChannelQueue.size();
    for (int i = 0; i < items; i++) {
        Signal signal = outChannelQueue.dequeue();
        emit processedData(signal);
    }

    outChannelQueue.clear();
    */


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
    conf.hostname = "146.190.122.149";
    conf.port = 1883;
}

void MQTTPublish::initMQTTCommunication()
{
    comm = new MQTTComm(this);
    comm->setHostName(conf.hostname);
    comm->setPort(conf.port);
    connect(comm, &MQTTComm::updateStatusConnection, this, [=](QString msg){
        qDebug() << "Status Connection" << msg;
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

