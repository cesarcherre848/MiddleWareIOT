// plugininterface.h
#ifndef MQTTSubscriber_H
#define MQTTSubscriber_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QMutex"
#include "QQueue"
#include "QList"
#include "Models/Signals.h" // modificar al cambiar de entorno
#include "Models/MSConf.h"
#include "mqttcomm.h"
#include "Utils/parserthread.h"

class MQTTSubscriber : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;

    MQTTSubscriber();
    ~MQTTSubscriber();

    void setSetup(const QMap<QString, QVariant> &newSetup) override;

    void setAsginedSignals(const QStringList &newAsginedSignals) override;

    QString getName() const override;

    void execute() override;

    void insertData(const Signal&) override;

    void setAsignedComponents(const QMap<QString, AssignedComponent>&) override;

    void setAlias(const QString &newAlias) override;

private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    MSConf conf;

    MQTTComm* comm = nullptr;

    QMap<QString, AssignedComponent> asignedComponents;

    QMutex mutex;

    QMap<TypeParser, ParserThread*> parsersThread;

    QMap<QString, TypeParser> topicTypeParser;

private:

    void getConf();

    void initMQTTCommunication();

    void stopsThreads();

    void waitThreads();

    void deleteThreads();


    void getTopicTypeParser();




    //QByteArray parseValuePayload(const Signal& data);

    //void applyComponentSignal(Signal &signal);

    //void publishMultipleTopics(QByteArray message, QStringList topics);


private slots:

    void recibeSignals(QList<Signal>);

    void computePayload(const QByteArray &message, QString topic);

signals:


};

#endif
