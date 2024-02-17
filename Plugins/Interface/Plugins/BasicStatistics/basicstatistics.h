// plugininterface.h
#ifndef BasicStatistics_H
#define BasicStatistics_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "../DataManagerLib/Models/Signals.h" // modificar al cambiar de entorno
#include "Models/BSConf.h"


class BasicStatistics : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;

    void setSetup(const QMap<QString, QVariant> &newSetup) override;

    void setAsginedSignals(const QStringList &newAsginedSignals) override;

    QString getName() const override;

    void execute() override;

    void insertData(const Signal&) override;



private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    BSConf conf;


private:

    void getBSConf();

    void computeOperation(Signal data, QQueue<Signal> &queue);



signals:


};

#endif
