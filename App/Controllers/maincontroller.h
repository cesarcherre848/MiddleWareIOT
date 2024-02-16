#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
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

    void initMQTTCommunication();
    void initDataManager();

private:

    MQTTComm* comm;
    QMap<QString, QString>mapIdComponent;
    DataManager* manager;



    //QSqlDatabase db;

private:

    //void InitDB();
    //void getDataFromDB();

public slots:

    //void updateStatusConnection();
};

#endif // MAINCONTROLLER_H
