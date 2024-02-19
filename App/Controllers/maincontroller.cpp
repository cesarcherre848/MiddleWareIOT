#include "maincontroller.h"
#include "QThread"
#include "payloaderbessd.h"


MainController::MainController(QObject *parent)
    : QObject{parent}
{

    initConfig();
    initDataManager();
    initMQTTCommunication();


    //this->mapIdComponent.insert("189301637","0108bb4d-218e-4ba0-9102-60fbdab3c97e");

    //IdNodes = {"189301637"};


}

MainController::~MainController()
{
    if(comm){
        comm->disconnect();
        delete comm;
    }

    if(manager){
        delete manager;
    }
}

void MainController::initConfig()
{
    bool infoLogs = settings.value("InfoLogs").toBool();
    if(!infoLogs){
        QLoggingCategory::setFilterRules(QStringLiteral("*.info=false"));
    }
}

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


        QThread* thread = new QThread(this);
        PayloadErbessd* payloadErbessdParser = new PayloadErbessd();
        payloadErbessdParser->setParent(this);

        payloadErbessdParser->setPayLoad(message, topic);


        QObject::connect(payloadErbessdParser, &PayloadErbessd::finished, thread, &QThread::quit);
        QObject::connect(payloadErbessdParser, &PayloadErbessd::finished, payloadErbessdParser, &PayloadErbessd::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);



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
        QObject::connect(thread, &QThread::started, payloadErbessdParser, &PayloadErbessd::execute);
        thread->start();

    });

    comm->connect();
}

void MainController::initDataManager()
{
    manager = new DataManager(settings);
    manager->setParent(this);
}

/*
void MainController::InitDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("146.190.122.149"); // Solo el nombre del host o la IP, sin el número de puerto
    db.setPort(5432);
    db.setDatabaseName("Empresa1");
    db.setUserName("root");
    db.setPassword("Mc05071995..");
    db.open();
}
*/

/*
void MainController::getDataFromDB()
{
    QSqlQuery query;
    query.prepare("SELECT \"Id_Node\", \"Id_Component\" FROM \"SensorComponent\" AS sc "
                  "where sc.\"Id_Node\" IN (:IdNodes)");
    query.bindValue(":IdNodes", IdNodes.join(","));



    if (!query.exec()) {
        qDebug() << "Error al ejecutar la consulta:" << query.lastError().text();
        return;
        db.close();
    }

    while (query.next()) {
        QString id_node = query.value(0).toString();
        QString id_component = query.value(1).toString();
        this->mapIdComponent.insert(id_node,id_component);
    }

    db.close();
}
*/

