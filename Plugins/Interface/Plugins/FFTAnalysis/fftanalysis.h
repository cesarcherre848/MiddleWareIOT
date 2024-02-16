// plugininterface.h
#ifndef FFTANALYSIS_H
#define FFTANALYSIS_H

#include "plugininterface.h"
#include "QObject"
#include "QtPlugin"
#include "QQueue"
#include "../DataManagerLib/Models/Signals.h" // modificar al cambiar de entorno
#include "Models/FFTConf.h"
#include "Models/ScalarsConf.h"


class FFTAnalysis : public PluginInterface {
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

    FFTConf conf;

    ScalarsConf scalarsConf;

    PhysicalQty uniformInputQty = PhysicalQty::other;

private:

    void getFFTConf();

    void getScalarsConf();

    void computeSingleChannel();

    void computeSingleFunction(Signal data, QQueue<Signal>& queue);


signals:

    //void processedData(const Signal&);
};

#endif
