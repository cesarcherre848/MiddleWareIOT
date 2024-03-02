#include "maincontroller.h"
#include "QThread"
#include "payloaderbessd.h"


MainController::MainController(QObject *parent)
    : QObject{parent}
{

    initConfig();
    initDataManager();
    //initMQTTCommunication();

}

MainController::~MainController()
{
    /*
    if(comm){
        //comm->disconnect();
        comm->deleteLater();
    }
    */

    qDebug() << "delete comm";
    if(manager){
        manager->deleteLater();
    }

    qDebug() << "delete manager";
}

void MainController::initConfig()
{
    bool infoLogs = settings.value("InfoLogs").toBool();
    if(!infoLogs){
        QLoggingCategory::setFilterRules(QStringLiteral("*.info=false"));
    }
}

/*
void MainController::initMQTTCommunication()
{
    comm = new MQTTComm(this);
    comm->setHostName("146.190.122.149");
    comm->setPort(1883);

    //comm->setSubTopic("prueba");




    connect(comm, &MQTTComm::updateStatusConnection, this, [=](QString msg){
        qDebug() << "Status Connection" << msg;



    });

    connect(comm, &MQTTComm::recievePayload, this, [=](const QByteArray &message, QString topic){
        //qDebug() << "topic" << QStringList(topic.split("/"));
        //qDebug() << "message" << QString(message);


        //QThread* thread = new QThread(this);
        //PayloadErbessd* payloadErbessdParser = new PayloadErbessd(this);

        //MQTTParser* parser = (MQTTParser*) payloadErbessdParser;

        //payloadErbessdParser->setPayLoad(message, topic);


        //QObject::connect(parser, &PayloadErbessd::finished, thread, &QThread::quit);
        //QObject::connect(parser, &PayloadErbessd::finished, parser, &PayloadErbessd::deleteLater);
        //QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        //connect(parser, SIGNAL(finished()), thread, SLOT(quit()));
        //connect(parser, SIGNAL(finished()), parser, SLOT(deleteLater()));
        //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));



        QObject::connect(payloadErbessdParser, &PayloadErbessd::updateSignals, this, [=](QList<Signal> data){
            //qDebug() << data;
            if(this->manager){
                int sizeData = data.size();
                for (int i=0; i < sizeData; i++){
                    this->manager->insertInputDataQueue(data[i]);
                }
            }
        });



        // Iniciar el hilo y ejecutar la tarea
        //QObject::connect(thread, &QThread::started, payloadErbessdParser, &PayloadErbessd::execute);
        //thread->start();

    });

    comm->connect();
}
*/
void MainController::initDataManager()
{
    manager = new DataManager(settings);
    manager->setParent(this);
}

void MainController::exitRequest()
{
    qDebug() << "Delete MainController";
    this->deleteLater();
}

