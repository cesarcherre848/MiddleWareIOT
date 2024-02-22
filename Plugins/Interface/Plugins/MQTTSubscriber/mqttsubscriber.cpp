#include "mqttsubscriber.h"
#include "QDebug"
#include <QJsonObject>
#include <QJsonDocument>
#include "QVariantList"
#include "Constants/textMaps.h"
#include "payloaderbessd.h"

//#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *MQTTSubscriber::newInstance()
{
    return new MQTTSubscriber();
}

MQTTSubscriber::MQTTSubscriber()
{
    comm = new MQTTComm(this);
}

MQTTSubscriber::~MQTTSubscriber()
{
    stopsThreads();
    waitThreads();
    deleteThreads();


    if(comm){
        comm->deleteLater();
    }
}

void MQTTSubscriber::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getConf();
    initInstancesParsers();
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

    if(setup.contains("topics")){
        QMap mapTopics = setup["topics"].toMap();
        foreach (QString key, mapTopics.keys()) {
            conf.parserTopics.insert(key, mapTopics[key].toStringList());
        }
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


    comm->setHostName(conf.hostname);
    comm->setPort(conf.port);
    connect(comm, &MQTTComm::updateStatusConnection, this, [=](QString msg){
        qWarning() << QString("%1 %2").arg(getName()).arg("Connections Status") << msg;
    });


    comm->connect();
}

void MQTTSubscriber::stopsThreads()
{
    mutex.lock();
    foreach (QThread* thread, parsersThread.values()) {
        if(thread){
            if(thread->isRunning()){
                thread->quit();
            }
        }
    }
    mutex.unlock();
}

void MQTTSubscriber::waitThreads()
{
    mutex.lock();
    foreach (QThread* thread, parsersThread.values()) {
        if(thread){
            if(thread->isRunning()){
                thread->wait();
            }
        }
    }
    mutex.unlock();
}

void MQTTSubscriber::deleteThreads()
{
    mutex.lock();

    foreach (ParserThread* thread, parsersThread.values()) {
        MQTTParser* parser = thread->getParser();
        if(parser){
            delete parser;
        }
    }

    qDeleteAll(parsersThread);
    mutex.unlock();
}

void MQTTSubscriber::initInstancesParsers()
{
    QMap<QString, QStringList> parserTopics = conf.parserTopics;

    foreach (QString key, parserTopics.keys()) {
        switch (invMapTypeParser[key]) {
        case TypeParser::ERB:
            parsersThread.insert(key,new ParserThread(new PayloadErbessd(this), this));
            break;
        default:
            break;
        }
    }

    qDebug() << parsersThread;
}




