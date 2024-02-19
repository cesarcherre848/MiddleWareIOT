#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#include <QtMqtt/QMqttClient>


const QMap<QMqttClient::ClientState, QString> mapState = {
    {QMqttClient::Disconnected, "Disconnected"},
    {QMqttClient::Connecting, "Connecting"},
    {QMqttClient::Connected, "Connected"}
};



#endif // TEXTMAPS_H
