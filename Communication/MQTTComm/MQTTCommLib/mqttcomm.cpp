#include "mqttcomm.h"
#include "QDebug"
#include "Constants/textMaps.h"

MQTTComm::MQTTComm(QObject *parent):
    QObject(parent)
{
    client = new QMqttClient(this);



    QObject::connect(client, &QMqttClient::connected, this, &MQTTComm::onConnected);
    QObject::connect(client, &QMqttClient::disconnected, this, &MQTTComm::onDisconnected);

    QObject::connect(client, &QMqttClient::stateChanged, this, &MQTTComm::onStateChanged);


    QObject::connect(client, &QMqttClient::messageReceived, this, [=](const QByteArray &payload, const QMqttTopicName &topic) {
        emit recievePayload(payload, topic.name());
    });



    reconnectTimer = new QTimer(this);
    reconnectTimer->setInterval(5000); // Configurar el intervalo del temporizador a 1 segundo
    QObject::connect(reconnectTimer, &QTimer::timeout, this, &MQTTComm::tryReconnect);

}

MQTTComm::~MQTTComm()
{
    if(client){
        delete client;
    }
}

void MQTTComm::setHostName(const QString &newHostName)
{
    hostName = newHostName;
}


void MQTTComm::setSubTopic(const QString &newSubTopic)
{
    if(!client){
        return;
    }


    QString topic = QString("prueba/#");
    if (client->state() == QMqttClient::Connected) {
        QMqttSubscription *subscription = client->subscribe(topic);
        if (!subscription) {
            qDebug() << "no se pudo subscribir";
        }
    }
}

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

    client->disconnectFromHost();
}

void MQTTComm::publishPayload(const QByteArray &message, QString topicString)
{
    if(!client){
        return;
    }
    QMqttTopicName topic(topicString);
    client->publish(topic, message);
}

void MQTTComm::onConnected()
{
    qDebug() << "Connected to broker";
    reconnectTimer->stop();
    setSubTopic("");
}

void MQTTComm::onStateChanged(QMqttClient::ClientState state)
{
    if (state == QMqttClient::Disconnected) {
        //qDebug() << "Disconnected. Reconnecting...";
        reconnectTimer->start(); // Iniciar el temporizador cuando cambia a estado desconectado
        //client->connectToHost();
    }
}

void MQTTComm::onDisconnected()
{
    qDebug() << "Disconnected from broker. Reconnecting... in 5 sec";
    reconnectTimer->start();
}

void MQTTComm::tryReconnect()
{
    qDebug() << "Attempting to reconnect...";
    client->connectToHost();
}

