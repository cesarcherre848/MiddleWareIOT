// plugininterface.h
#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "Models/Signals.h" // modificar al cambiar de entorno
#include "Models/EVConf.h"

class Envelope : public PluginInterface {
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

    void setAlias(const QString &newAlias) override;




private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    EVConf conf;

    QString alias;

    //ScalarsConf scalarsConf;

    //PhysicalQty uniformInputQty = PhysicalQty::other;

private:


    void getEVConf();

    /*
    void getScalarsConf();

    void computeSingleChannel();
    */

    void computeOperation(Signal data, QQueue<Signal>& queue);


signals:


};

#endif
