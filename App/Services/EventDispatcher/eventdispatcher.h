#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <QObject>
#include "QSettings"

#include "QThread"
#include "Models/confDispatcher.h"

class MQTTComm;

class EventDispatcher : public QObject
{
    Q_OBJECT
public:

    static EventDispatcher& instance();

    ~EventDispatcher();

    EventDispatcher(EventDispatcher const&) = delete;
    void operator=(EventDispatcher const&) = delete;

private:
    EventDispatcher();

    void initMQTTCommunication();

private:


    MQTTComm* comm = nullptr;

private slots:

    void computePayload(const QByteArray &message, QString topic);

    void reciveUpdateAction(ActionUpdate);

signals:


    void updateAssignedComponent();
};

#endif // EVENTDISPATCHER_H
