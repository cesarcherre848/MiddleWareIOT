#ifndef BASESERVICE_H
#define BASESERVICE_H
#include "QCoreApplication"
#include "QStringList"
#include "Models/Operation.h"
#include "../Interface/plugininterface.h"


class BaseService : public QObject
{
    Q_OBJECT
public:
    explicit BaseService();

public:

    QStringList directoryPlugins;

    QList<Operation> operations;

    QList<PluginInterface *> operationsInstances;

    QMap<QString, AssignedComponent> asignedComponents;

    QString dirConfig;

    QString dirRel = QCoreApplication::applicationDirPath();

public:

    void loadPluginIntances();

    void executeAllOperations();

    void insertDatatoOperation(const Signal& data);

    void setAsignedComponents(const QMap<QString, AssignedComponent> &newAsignedComponents);

    void loadConfig();

private:

    PluginInterface *getPluginInterface(Operation operation);

    void jsonByteArrayToOperation(QByteArray byteArray);


public slots:

    void reciveProcessedData(const Signal&);

signals:

    void returnDataToInputQueue(const Signal&);

};

#endif // BASESERVICE_H
