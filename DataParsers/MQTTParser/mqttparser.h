// plugininterface.h
#ifndef MQTTPARSER_H
#define MQTTPARSER_H

#include <QtPlugin>
#include "QMap"
#include "Models/Signals.h"

class MQTTParser : public QObject {

    Q_OBJECT

public:
    explicit MQTTParser(QObject *parent = nullptr);
    ~MQTTParser();


    void setPayLoad(const QByteArray &_byteArray, const QString &_topic);


    QString getTopic() const;

    QByteArray getByteArray() const;

private:

    QByteArray byteArray;
    QString topic;


public slots:

    virtual void execute(){};

signals:

    //void finished();

    //void updateSignals(QList<Signal>);



};



#endif // MQTTPARSER_H
