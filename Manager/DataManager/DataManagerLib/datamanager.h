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
#include "QSettings"
#include "Services/apirequest.h"

class DATAMANAGER_EXPORT DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QSettings& _settings);
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

    InputFlow* inputFlow = nullptr;
    Processor* processor = nullptr;
    OutputFlow* outputFlow = nullptr;

    ApiRequest* apiRequest = nullptr;


    QSqlDatabase db;
    QMap<QString, AssignedComponent> asignedComponents;
    QStringList idNodes;

    QSettings &settings;

    QString dirRel = QCoreApplication::applicationDirPath();

private:

    void InitDB();
    void getDataFromDB();

    QMap<QString, QString> byteArrayJsonToChannels(QByteArray bytearray);

    QString formatIdNodes();

    void loadKnowIdNodes();

public slots:

    void updateEventAssignedComponent();

private slots:

    void updateAssignedComponent(QMap<QString, AssignedComponent> asignedComponents);

};

#endif // DATAMANAGER_H
