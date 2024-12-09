// plugininterface.h
#ifndef Save2DData_H
#define Save2DData_H

#include "plugininterface.h"
#include "QObject"
#include "QQueue"
#include "Models/Signals.h"
#include "Models/S2DConf.h"
#include "QJsonObject"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class Save2DData : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginInterface" FILE "MyPlugin.json")
    Q_INTERFACES(PluginInterface)

public:


    PluginInterface *newInstance() override;
    Save2DData();
    ~Save2DData();

    void setSetup(const QMap<QString, QVariant> &newSetup) override;

    void setAsginedSignals(const QStringList &newAsginedSignals) override;

    QString getName() const override;

    void execute() override;

    void insertData(const Signal&) override;

    void setAsignedComponents(const QMap<QString, AssignedComponent>&) override;

    void setAlias(const QString &newAlias) override;



private:

    QString alias = "";

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    QMap<QString, AssignedComponent> asignedComponents;

    S2DConf conf;

private:

    void getS2DConf();

    void applyComponentSignal(Signal &signal);

    void completeQuery(Signal &signal, QString& query, int& count);

    std::vector<double> getXVector1DData(double init, int size, double delta);

    void convertSignalToJson(Signal &signal, QJsonObject& jsonObject);

    void postJsonAsync(const QUrl &url,
                       const QJsonObject &jsonObject,
                       QObject *parent = nullptr);

};

#endif
