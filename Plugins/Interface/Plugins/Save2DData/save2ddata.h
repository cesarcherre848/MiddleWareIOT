// plugininterface.h
#ifndef Save2DData_H
#define Save2DData_H

#include "plugininterface.h"
#include "QObject"
#include "QQueue"
#include "Models/Signals.h"
#include <QtSql>
#include "Models/S2DConf.h"


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



private:

    QMap<QString, QVariant> setup;

    QStringList asginedSignals;

    QQueue<Signal> inputDataQueue;

    QSqlDatabase db;

    QMap<QString, AssignedComponent> asignedComponents;

    S2DConf conf;

    QTimer *reconnectTimer = nullptr;

    int currentReconnectionAttempts = 0;

private:

    void getS2DConf();

    std::string vectorToText(const std::vector<double>& data);

    void applyComponentSignal(Signal &signal);

    void completeQuery(Signal &signal, QString& query, int& count);

    std::vector<double> getXVector1DData(double init, int size, double delta);

    void InitTimerReconnection();


private slots:

    void tryReconnect();

public slots:

    void InitDB();

};

#endif
