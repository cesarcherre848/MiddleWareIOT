#include "mqttsubscriber.h"
#include "QDebug"
#include <QJsonObject>
#include <QJsonDocument>
#include "QVariantList"
#include "Constants/textMaps.h"
#include "payloaderbessd.h"
#include <QMqttTopicFilter>

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

    qDebug() << this;
    qDebug() << "Destroy MQTTSubscriber";

    this->blockSignals(true);
    disconnect(comm, &MQTTComm::recievePayload, this,  &MQTTSubscriber::computePayload);

    /*
    QList<QThread *> threadList = findChildren<QThread *>();
    for (QThread *thread : threadList) {
        thread->quit();
        thread->wait();
        thread->deleteLater();
    }

    QList<MQTTParser*> parserList = findChildren<MQTTParser*>();
    for (MQTTParser*parser : parserList) {
        parser->deleteLater();
    }
*/


    if(comm){
        comm->deleteLater();
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

    if(setup.contains("topics")){
        QMap mapTopics = setup["topics"].toMap();
        foreach (QString key, mapTopics.keys()) {
            conf.parserTopics.insert(key, mapTopics[key].toStringList());
        }
    }

    getTopicTypeParser();


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


    connect(comm, &MQTTComm::recievePayload, this,  &MQTTSubscriber::computePayload);
    //connect(comm, &MQTTComm::recievePayload, this, [=](const QByteArray &message, QString topic){
        //computePayload(message, topic);
    //});


    comm->connect();
}





void MQTTSubscriber::getTopicTypeParser()
{
    QMap<QString, QStringList> parserTopics = conf.parserTopics;
    foreach (QString key, parserTopics.keys()) {
        QStringList topics = parserTopics[key];
        foreach (QString topic, topics) {
            if(!invMapTypeParser.keys().contains(key)){
                continue;
            }
            TypeParser typeParser = invMapTypeParser[key];
            topicTypeParser.insert(topic, typeParser);
        }
    }

}

void MQTTSubscriber::computePayload(const QByteArray &message, QString topic)
{

    QStringList topics = topicTypeParser.keys();

    bool matchTopic = false;
    QMqttTopicName topicN(topic);
    foreach (QString _topic, topics) {
        QMqttTopicFilter _topicN(_topic);
        if(_topicN.match(topicN)){
            matchTopic = true;
            break;
        }
    }

    if(!matchTopic){
        return;
    }



    TypeParser typeParser = topicTypeParser[topic];

    if(typeParser == TypeParser::ERB){
        QThread* thread = new QThread(this);
        PayloadErbessd* payloadErbessdParser = new PayloadErbessd(this);
        payloadErbessdParser->setPayLoad(message, topic);
        MQTTParser* parser = (MQTTParser*) payloadErbessdParser;
        connect(parser, SIGNAL(finished()), thread, SLOT(quit()));
        connect(parser, SIGNAL(finished()), parser, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(parser, SIGNAL(updateSignals(QList<Signal>)), this, SLOT(recibeSignals(QList<Signal>)));

        QObject::connect(thread, &QThread::started, payloadErbessdParser, &PayloadErbessd::execute);
        thread->start();
    }


}

void MQTTSubscriber::recibeSignals(QList<Signal> data)
{
    for (int i = 0; i < data.size(); ++i) {
        emit processedData(data[i]);
    }
}




