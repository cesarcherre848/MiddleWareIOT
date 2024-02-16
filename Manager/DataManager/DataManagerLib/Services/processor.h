#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include "QTimer"
#include "Models/Signals.h"
#include "QMutex"
#include "QSet"
#include "QQueue"
#include "Models/Operation.h"
#include "../Interface/plugininterface.h"
#include "baseservice.h"

class Processor : public BaseService
{

    Q_OBJECT

public:
    //explicit Processor(QObject *parent = nullptr);
    explicit Processor(int& processInterval, int& maxQueuesProcessItems);
    ~Processor();

    void startProcessing();

    void stopProcessing();

signals:

    //void returnDataToInputQueue(const Signal&);

    void newProcessData(const Signal&);


public slots:

    void process();

    void insertData(const Signal&);

    //void reciveProcessedData(const Signal&);



private:


    QQueue<Signal> processDataQueue;
    //QMutex& inputMutex_;
    //QSet<QString>& processedIds_;
    int& processInterval_;
    int& maxQueuesProcessItems_;
    QTimer* timer; // Temporizador para el procesamiento periódico
    bool processing = false;
    //QList<Operation> operations;

    //QList<PluginInterface *> operationsInstances;


    //QStringList directoryPlugins;



private:

    void loadOperations();

    //void loadOperaitonInstances();

    PluginInterface *getPluginInterface(Operation operation);

    //void executeAllOperations();

    //void insertDatatoOperation(const Signal& data);

    void mainTimeout();

public:

    QMutex mutex;


};

#endif // PROCESSOR_H
