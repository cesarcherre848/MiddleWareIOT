#include "eventdispatcher.h"
#include "QDebug"
#include "Parsers/eventparser.h"
#include "QThread"

EventDispatcher &EventDispatcher::instance()
{
    static EventDispatcher _instance;
    return _instance;
}

EventDispatcher::EventDispatcher() {

    qDebug() << "Init event Dispatcher";

    comm = new MQTTComm();
    initMQTTCommunication();

}

void EventDispatcher::initMQTTCommunication()
{
    QString hostname = "146.190.122.149";
    int port = 1883;

    if(port == 0){
        return;
    }

    if(hostname.isEmpty()){
        return;
    }

    comm->setHostName(hostname);
    comm->setPort(port);
    //comm->setSubTopics({"events/#"});


    connect(comm, &MQTTComm::recievePayload, this,  &EventDispatcher::computePayload);

    comm->connect();
}

void EventDispatcher::computePayload(const QByteArray &message, QString topic)
{
    QThread* thread = new QThread(this);
    EventParser* parser = new EventParser(this);
    parser->setPayLoad(message, topic);

    connect(parser, SIGNAL(finished()), thread, SLOT(quit()));
    connect(parser, SIGNAL(finished()), parser, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(parser, SIGNAL(updateAction(ActionUpdate)), this, SLOT(reciveUpdateAction(ActionUpdate)));
    QObject::connect(thread, &QThread::started, parser, &EventParser::execute);
    thread->start();
}

void EventDispatcher::reciveUpdateAction(ActionUpdate action)
{
    switch (action) {
    case ActionUpdate::AUassignedComponent :
        emit updateAssignedComponent();
        break;
    default:
        break;
    }
}


EventDispatcher::~EventDispatcher()
{
    if(comm){
        comm->deleteLater();
    }
}

