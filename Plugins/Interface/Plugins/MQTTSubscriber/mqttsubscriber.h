// plugininterface.h
#ifndef MQTTSubscriber_H
#define MQTTSubscriber_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "../DataManagerLib/Models/Signals.h" // modificar al cambiar de entorno
#include "Models/MSConf.h"
#include "mqttcomm.h"


class MQTTSubscriber : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;

    ~MQTTSubscriber();

    void setSetup(const QMap<QString, QVariant> &newSetup) override;

    void setAsginedSignals(const QStringList &newAsginedSignals) override;

    QString getName() const override;

    void execute() override;

    void insertData(const Signal&) override;

    void setAsignedComponents(const QMap<QString, AssignedComponent>&) override;


private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    MSConf conf;

    MQTTComm* comm;

    QMap<QString, AssignedComponent> asignedComponents;

private:

    void getConf();

    void initMQTTCommunication();

    //QByteArray parseValuePayload(const Signal& data);

    //void applyComponentSignal(Signal &signal);

    //void publishMultipleTopics(QByteArray message, QStringList topics);



signals:


};

#endif
