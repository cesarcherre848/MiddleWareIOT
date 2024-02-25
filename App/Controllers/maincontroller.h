#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "Utils/globalresources.h"
#include "mqttcomm.h"
#include "datamanager.h"


class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

signals:

public:

    void initConfig();
    void initMQTTCommunication();
    void initDataManager();

private:

    MQTTComm* comm;
    QMap<QString, QString>mapIdComponent;
    DataManager* manager;
    QSettings& settings = GlobalResources::getSettings();




    //QSqlDatabase db;

private:

    //void InitDB();
    //void getDataFromDB();

public slots:

    void exitRequest();

    //void updateStatusConnection();
};

#endif // MAINCONTROLLER_H
