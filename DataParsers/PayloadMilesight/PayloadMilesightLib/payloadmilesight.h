#ifndef PAYLOADMILESIGHT_H
#define PAYLOADMILESIGHT_H

#include "PayloadMilesight_global.h"
#include "Models/MilesightData.h"
#include "QObject"
#include "QMap"
//#include "Models/Signals.h"
#include "mqttparser.h"

class PAYLOADMILESIGHT_EXPORT PayloadMilesight : public MQTTParser
{
    Q_OBJECT

public:
    explicit PayloadMilesight(QObject *parent = nullptr);
    ~PayloadMilesight();

    void setPayLoad(const QByteArray &byteArray, QString topic);

private:

    void parseProcessData(MilesightData &data, const QJsonObject& json);

    void dataToSignal(MilesightData &data);



private:

    QByteArray byteArray;
    QString topic;


public slots:

    void execute();


signals:

    //void finished();

    //void updateSignals(QList<Signal>);

};

#endif // PAYLOADMILESIGHT_H
