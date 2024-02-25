#ifndef BASESERVICE_H
#define BASESERVICE_H
#include "QCoreApplication"
#include "QSettings"
#include "QStringList"
#include "QQueue"
#include "QTimer"
#include "Models/Operation.h"
#include "plugininterface.h"



class BaseService : public QObject
{
    Q_OBJECT
public:
    explicit BaseService(QSettings &_settings);
    ~BaseService();

public:


    QList<Operation> operations;

    QMap<QString, AssignedComponent> asignedComponents;

    QString dirConfig;

    QString dirRel = QCoreApplication::applicationDirPath();




public:

    void loadPluginIntances();

    void executeAllOperations();

    void insertDatatoOperation(const Signal& data);

    void setAsignedComponents(const QMap<QString, AssignedComponent> &newAsignedComponents);

    void loadConfig();

    void mainTimeout();

    void setInterval(float newInterval);

    void addDirectoryPlugins(QString);

    void printOperationsInstances();

    void enqueueDataQueue(const Signal& data);

    Signal dequeueDataQueue();

    void insertData(const Signal & data);

    int sizeDataQueue();



    QSettings &getSettings() const;

private:

    QTimer* timer = nullptr;

    float interval = 2.;

    QList<std::shared_ptr<PluginInterface>> operationsInstances;

    QStringList directoryPlugins;

    QQueue<Signal> dataQueue;

    QMutex mutex;

    QSettings& settings;




private:

    std::shared_ptr<PluginInterface> getPluginInterface(Operation operation);

    void jsonByteArrayToOperation(QByteArray byteArray);


public slots:

    void reciveProcessedData(const Signal&);

    virtual void execute(){};

signals:

    void returnDataToInputQueue(const Signal&);

};

#endif // BASESERVICE_H
