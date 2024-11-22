#include "mqttcomm.h"
#include "QDebug"


MQTTComm::MQTTComm(QObject *parent):
    QObject(parent)
{

    reconnectTimer = new QTimer(this);

    client = new QMqttClient(this);
    client->setCleanSession(false);



    QObject::connect(client, &QMqttClient::connected, this, &MQTTComm::onConnected);
    QObject::connect(client, &QMqttClient::disconnected, this, &MQTTComm::onDisconnected);

    QObject::connect(client, &QMqttClient::stateChanged, this, &MQTTComm::onStateChanged);


    QObject::connect(client, &QMqttClient::messageReceived, this, [=](const QByteArray &payload, const QMqttTopicName &topic) {

        emit recievePayload(payload, topic.name());
    });




    reconnectTimer->setInterval(5000); // Configurar el intervalo del temporizador a 1 segundo
    QObject::connect(reconnectTimer, &QTimer::timeout, this, &MQTTComm::tryReconnect);

}

MQTTComm::~MQTTComm()
{
    reconnectTimer->stop();
    QObject::disconnect(client, &QMqttClient::disconnected, this, &MQTTComm::onDisconnected);
    QObject::disconnect(client, &QMqttClient::disconnected, this, &MQTTComm::onDisconnected);
    QObject::disconnect(client, &QMqttClient::stateChanged, this, &MQTTComm::onStateChanged);

    client->disconnectFromHost();
    reconnectTimer->deleteLater();

    qInfo() << QString("Disconnected MQTT Broker (%1)").arg(hostName).toStdString().c_str();

    if(client){
        client->deleteLater();
    }
}

void MQTTComm::setHostName(const QString &newHostName)
{
    hostName = newHostName;
}


/*
void MQTTComm::setSubTopic(const QString &newSubTopic)
{
    if(!client){
        return;
    }


    QString topic = QString("prueba/#");
    if (client->state() == QMqttClient::Connected) {
        QMqttSubscription *subscription = client->subscribe(topic);
        if (!subscription) {
            qWarning() << "Cannot subscribe topic";
        }
    }
}
*/

void MQTTComm::setPort(int newPort)
{
    port = newPort;
}

void MQTTComm::connect()
{
    if(!client){
        return;
    }

    client->setHostname(hostName);
    client->setPort(port);
    client->connectToHost();
}

void MQTTComm::disconnect()
{
    if(!client){
        return;
    }
}

void MQTTComm::publishPayload(const QByteArray &message, QString topicString)
{
    if(!client){
        return;
    }
    QMqttTopicName topic(topicString);
    client->publish(topic, message);
}

void MQTTComm::setSubTopics(const QStringList &newSubTopics)
{
    subTopics = newSubTopics;
}

void MQTTComm::onConnected()
{
    qInfo() << QString("Connection to MQTT Broker (%1) Succesfully").arg(hostName).toStdString().c_str();
    reconnectTimer->stop();


    foreach(QString topic, subTopics){
        client->subscribe(topic);
        qDebug() << topic;
    }
}

void MQTTComm::onStateChanged(QMqttClient::ClientState state)
{
    if (state == QMqttClient::Disconnected) {
        reconnectTimer->start();
    }
}

void MQTTComm::onDisconnected()
{
    qWarning() << QString("Disconnected from MQTT Broker (%1). Reconnecting... in 5 sec").arg(hostName).toStdString().c_str();
    reconnectTimer->start();
}

void MQTTComm::tryReconnect()
{
    qWarning() << QString("Attempting to reconnect MQTT Broker (%1)...").arg(hostName).toStdString().c_str();
    client->connectToHost();
}

