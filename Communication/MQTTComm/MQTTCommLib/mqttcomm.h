#ifndef MQTTCOMM_H
#define MQTTCOMM_H

#include "MQTTComm_global.h"
#include "QString"

#ifdef __linux__
#include <QtMqtt/qmqttclient.h>
#elif _WIN32
#include <QtMqtt/QMqttClient>
#endif

#include "QObject"
#include "QTimer"

class MQTTCOMM_EXPORT MQTTComm : public QObject
{

    Q_OBJECT

public:
    explicit MQTTComm(QObject *parent = nullptr);
    ~MQTTComm();

    void setHostName(const QString &newHostName);

    //void setSubTopic(const QString &newSubTopic);

    void setPort(int newPort);

    void connect();

    void disconnect();

    QMqttClient* client = nullptr;

    void publishPayload(const QByteArray &message, QString topic);

    void setSubTopics(const QStringList &newSubTopics);

private:

    QString hostName;
    int port;
    //QString subTopic;
    QTimer *reconnectTimer = nullptr;

    QStringList subTopics;

signals:

    void updateStatusConnection(QString);

    void recievePayload(const QByteArray &message, QString topic);


public slots:

    void onConnected();

    void onStateChanged(QMqttClient::ClientState state);

    void onDisconnected();

    void tryReconnect();
};


#endif // MQTTCOMM_H
