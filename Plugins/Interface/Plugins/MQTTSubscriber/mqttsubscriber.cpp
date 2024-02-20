#include "mqttsubscriber.h"
#include "QDebug"
#include <QJsonObject>
#include <QJsonDocument>
//#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *MQTTSubscriber::newInstance()
{
    return new MQTTSubscriber();
}

MQTTSubscriber::~MQTTSubscriber()
{
    if(comm){
        comm->disconnect();
        delete comm;
    }
}

void MQTTSubscriber::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getConf();
    initMQTTCommunication();

}

void MQTTSubscriber::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;


}

QString MQTTSubscriber::getName() const
{
    return "MQTTSubscriber";
}

void MQTTSubscriber::execute()
{

    if(!comm){
        return;
    }



}


void MQTTSubscriber::insertData(const Signal & data)
{

    if(asginedSignals.contains(data.name)){
        if(data.type != Type::value){
            return;
        }

        inputDataQueue.enqueue(data);
    }
}

void MQTTSubscriber::setAsignedComponents(const QMap<QString, AssignedComponent> & newAsignedComponents)
{
    asignedComponents = newAsignedComponents;
}




void MQTTSubscriber::getConf()
{
    if(setup.contains("hostname")){
        QString hostname = setup["hostname"].toString();
        conf.hostname = hostname;
    }
    if(setup.contains("port")){
        int port = setup["port"].toInt();
        conf.port = port;
    }


}

void MQTTSubscriber::initMQTTCommunication()
{
    if(conf.port == 0){
        return;
    }

    if(conf.hostname.isEmpty()){
        return;
    }

    comm = new MQTTComm(this);
    comm->setHostName(conf.hostname);
    comm->setPort(conf.port);
    connect(comm, &MQTTComm::updateStatusConnection, this, [=](QString msg){
        qWarning() << QString("%1 %2").arg(getName()).arg("Connections Status") << msg;
    });
    comm->connect();
}


