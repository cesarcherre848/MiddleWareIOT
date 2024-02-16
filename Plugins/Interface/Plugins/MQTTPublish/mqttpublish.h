// plugininterface.h
#ifndef MQTTPublish_H
#define MQTTPublish_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "../DataManagerLib/Models/Signals.h" // modificar al cambiar de entorno
#include "Models/MPConf.h"
#include "mqttcomm.h"


class MQTTPublish : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;

    ~MQTTPublish();

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

    MPConf conf;

    MQTTComm* comm;

    QMap<QString, AssignedComponent> asignedComponents;

private:

    void getConf();

    void initMQTTCommunication();

    QByteArray parseValuePayload(const Signal& data);

    void applyComponentSignal(Signal &signal);



signals:


};

#endif
