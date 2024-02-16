#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "DataManager_global.h"
#include "QList"
#include "Models/Signals.h"
#include "QMutex"
#include "QQueue"
#include "QTimer"
#include "QThread"
#include "Services/inputflow.h"
#include "Services/processor.h"
#include "Services/outputflow.h"

class DATAMANAGER_EXPORT DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();

    void insertInputDataQueue(const Signal& signal);

    void setProcessInterval(int newProcessInterval);

    void setMaxQueuesProcessItems(int newMaxQueuesProcessItems);

private:

    QQueue<Signal> inputDataQueue;
    //QMutex mutex;
    QSet<QString> processedIds;
    int processInterval = 100;
    int maxQueuesProcessItems = 300;

    //QTimer* sizeCheckTimer;

    InputFlow* inputFlow;
    Processor* processor;
    OutputFlow* outputFlow;


    QSqlDatabase db;
    QMap<QString, AssignedComponent> asignedComponents;
    QStringList idNodes;


private:

    void InitDB();
    void getDataFromDB();

    QMap<QString, QString> byteArrayJsonToChannels(QByteArray bytearray);

};

#endif // DATAMANAGER_H
