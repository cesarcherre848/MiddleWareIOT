#ifndef PAYLOADERBESSD_H
#define PAYLOADERBESSD_H

#include "PayloadErbessd_global.h"
#include "Models/ErbessdData.h"
#include "QObject"
#include "QMap"
#include "../DataManagerLib/Models/Signals.h"
#include "mqttparser.h"

class PAYLOADERBESSD_EXPORT PayloadErbessd : public MQTTParser
{
    Q_OBJECT

public:
    explicit PayloadErbessd(QObject *parent = nullptr);

    void setPayLoad(const QByteArray &byteArray, QString topic);

private:

    void parseProcessData(ErbessdData &data, const QJsonObject& json);

    void parseRawData(ErbessdData &data, const QJsonObject& json);

    void vectorFromJsonArray(std::vector<double>& vector ,const QJsonArray& data0);

    void dataProcessToSignal(ErbessdData &data);

    void dataRawToSignal(ErbessdData &data);

    void dataToSignal(ErbessdData &data);



private:

    QByteArray byteArray;
    QString topic;


public slots:

    void execute();


signals:

    void finished();

    void updateSignals(QList<Signal>);

};

#endif // PAYLOADERBESSD_H
