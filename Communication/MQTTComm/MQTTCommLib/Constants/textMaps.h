#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#ifdef __linux__
#include <QtMqtt/qmqttclient.h>
#elif _WIN32
#include <QtMqtt/QMqttClient>
#endif



const QMap<QMqttClient::ClientState, QString> mapState = {
    {QMqttClient::Disconnected, "Disconnected"},
    {QMqttClient::Connecting, "Connecting"},
    {QMqttClient::Connected, "Connected"}
};



#endif // TEXTMAPS_H
