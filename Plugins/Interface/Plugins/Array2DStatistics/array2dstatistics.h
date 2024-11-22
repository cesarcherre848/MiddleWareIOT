// plugininterface.h
#ifndef Array2DStatistics_H
#define Array2DStatistics_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "../DataManagerLib/Models/Signals.h" // modificar al cambiar de entorno
#include "Models/A2DSConf.h"


class Array2DStatistics : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;

    void setSetup(const QMap<QString, QVariant> &newSetup) override;

    void setAsginedSignals(const QStringList &newAsginedSignals) override;

    void setAlias(const QString &newAlias) override;

    QString getName() const override;

    void execute() override;

    void insertData(const Signal&) override;



private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    A2DSConf conf;

    QString alias;


private:

    void getA2DSConf();

    void computeOperation(Signal data, QQueue<Signal> &queue);



signals:


};

#endif
