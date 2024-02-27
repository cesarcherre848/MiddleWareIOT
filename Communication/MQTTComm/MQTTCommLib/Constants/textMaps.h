#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#ifdef __linux__
#include <QtMqtt/qmqttclient.h>
#elif Q_OS_WIN
#include <QtMqtt/QMqttClient>
#endif



const QMap<QMqttClient::ClientState, QString> mapState = {
    {QMqttClient::Disconnected, "Disconnected"},
    {QMqttClient::Connecting, "Connecting"},
    {QMqttClient::Connected, "Connected"}
};



#endif // TEXTMAPS_H
