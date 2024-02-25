#include "payloaderbessd.h"
#include "QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Models/ErbessdData.h"
#include "Constants/textMaps.h"
#include "QDateTime"



PayloadErbessd::PayloadErbessd(QObject *parent)
    : MQTTParser{parent}
{


}

PayloadErbessd::~PayloadErbessd()
{

}

void PayloadErbessd::setPayLoad(const QByteArray &byteArray, QString topic)
{

    this->byteArray = byteArray;
    this->topic = topic;


}

void PayloadErbessd::parseProcessData(ErbessdData &data, const QJsonObject &json)
{
    data.type = processData;

    const QJsonValue &tempValue = json["temperature"];

    if(tempValue.isDouble()){
        data.temperature = tempValue.toDouble();
    }

    const QJsonValue &battValue = json["battery"];

    if(battValue.isDouble()){
        data.batteryLevel = battValue.toDouble();
    }

    const QJsonValue &timestamp = json["timestamp"];
    if(timestamp.isDouble()){
        data.timestamp = QDateTime::fromSecsSinceEpoch(timestamp.toInt());
    }

    QJsonArray arrayRms = json["rms"].toArray();
    const QJsonValue &rmsXValue = arrayRms.at(0);
    const QJsonValue &rmsYValue = arrayRms.at(1);
    const QJsonValue &rmsZValue = arrayRms.at(2);

    if(rmsXValue.isDouble()){
        data.rmsX = rmsXValue.toDouble();
    }

    if(rmsYValue.isDouble()){
        data.rmsY = rmsYValue.toDouble();
    }

    if(rmsZValue.isDouble()){
        data.rmsZ = rmsZValue.toDouble();
    }
}

void PayloadErbessd::parseRawData(ErbessdData &data, const QJsonObject &json)
{
    data.type = rawData;

    const QJsonValue &timestamp = json["timestamp"];
    if(timestamp.isDouble()){
        data.timestamp = QDateTime::fromSecsSinceEpoch(timestamp.toInt());
    }

    const QJsonValue &rateValue = json["sampleRate"];

    if(rateValue.isDouble()){
        data.rate = rateValue.toDouble();
    }

    QJsonArray arrayData = json["data"].toArray();

    if(arrayData.size() != 3){
        return;
    }

    QJsonArray data0 = arrayData.at(0).toArray();
    QJsonArray data1 = arrayData.at(1).toArray();
    QJsonArray data2 = arrayData.at(2).toArray();

    std::vector<double> vector0;
    std::vector<double> vector1;
    std::vector<double> vector2;

    vectorFromJsonArray(vector0, data0);
    vectorFromJsonArray(vector1, data1);
    vectorFromJsonArray(vector2, data2);

    data.ch0 = vector0;
    data.ch1 = vector1;
    data.ch2 = vector2;

}

void PayloadErbessd::vectorFromJsonArray(std::vector<double> &vector, const QJsonArray &data)
{

    vector.reserve(data.size());

    std::transform(data.begin(), data.end(), std::back_inserter(vector),
                   [](const QJsonValue &value) {
                       if (value.isDouble()) {
                           return value.toDouble();
                       } else {

                           return 0.0;
                       }
                   });

}

void PayloadErbessd::dataProcessToSignal(ErbessdData &data)
{

    Signal signalTemp;
    signalTemp.name = QString("%1_ERB_Temperature").arg(data.idNode);
    signalTemp.idNode = data.idNode;
    signalTemp.qty = PhysicalQty::temperature;
    signalTemp.value = data.temperature;
    signalTemp.timestamp = data.timestamp;
    signalTemp.unit = "deg.C";
    signalTemp.type = Type::value;

    Signal signalBatt;
    signalBatt.name = QString("%1_ERB_Battery").arg(data.idNode);
    signalBatt.idNode = data.idNode;
    signalBatt.qty = PhysicalQty::voltage;
    signalBatt.value = data.batteryLevel;
    signalBatt.timestamp = data.timestamp;
    signalBatt.unit = "v";
    signalBatt.type = Type::value;


    Signal signalRmsX;
    signalRmsX.name = QString("%1_ERB_Velocity_ch0_RMS").arg(data.idNode);
    signalRmsX.idNode = data.idNode;
    signalRmsX.channel = "ch0";
    signalRmsX.qty = PhysicalQty::velocity;
    signalRmsX.value = data.rmsX;
    signalRmsX.timestamp = data.timestamp;
    signalRmsX.unit = "mm/s";
    signalRmsX.type = Type::value;

    Signal signalRmsY;
    signalRmsY.name = QString("%1_ERB_Velocity_ch1_RMS").arg(data.idNode);
    signalRmsY.idNode = data.idNode;
    signalRmsY.channel = "ch1";
    signalRmsY.qty = PhysicalQty::velocity;
    signalRmsY.value = data.rmsY;
    signalRmsY.timestamp = data.timestamp;
    signalRmsY.unit = "mm/s";
    signalRmsY.type = Type::value;


    Signal signalRmsZ;
    signalRmsZ.name = QString("%1_ERB_Velocity_ch2_RMS").arg(data.idNode);
    signalRmsZ.idNode = data.idNode;
    signalRmsZ.channel = "ch2";
    signalRmsZ.qty = PhysicalQty::velocity;
    signalRmsZ.value = data.rmsZ;
    signalRmsZ.timestamp = data.timestamp;
    signalRmsZ.unit = "mm/s";
    signalRmsZ.type = Type::value;


    emit updateSignals({signalTemp, signalBatt, signalRmsX, signalRmsY, signalRmsZ});

}

void PayloadErbessd::dataRawToSignal(ErbessdData &data)
{

    Signal signalCh0;
    signalCh0.name = QString("%1_ERB_Accelerometer_ch0").arg(data.idNode);
    signalCh0.idNode = data.idNode;
    signalCh0.channel = "ch0";
    signalCh0.qty = PhysicalQty::acceleration;
    signalCh0.value = -1.;
    signalCh0.timestamp = data.timestamp;
    signalCh0.unit = "g";
    signalCh0.type = Type::array1D;
    signalCh0.array1D = data.ch0;
    signalCh0.rate = data.rate;

    Signal signalCh1;
    signalCh1.name = QString("%1_ERB_Accelerometer_ch1").arg(data.idNode);
    signalCh1.idNode = data.idNode;
    signalCh1.channel = "ch1";
    signalCh1.qty = PhysicalQty::acceleration;
    signalCh1.value = -1.;
    signalCh1.timestamp = data.timestamp;
    signalCh1.unit = "g";
    signalCh1.type = Type::array1D;
    signalCh1.array1D = data.ch1;
    signalCh1.rate = data.rate;

    Signal signalCh2;
    signalCh2.name = QString("%1_ERB_Accelerometer_ch2").arg(data.idNode);
    signalCh2.idNode = data.idNode;
    signalCh2.channel = "ch2";
    signalCh2.qty = PhysicalQty::acceleration;
    signalCh2.value = -1.;
    signalCh2.timestamp = data.timestamp;
    signalCh2.unit = "g";
    signalCh2.type = Type::array1D;
    signalCh2.array1D = data.ch2;
    signalCh2.rate = data.rate;


    emit updateSignals({signalCh0, signalCh1, signalCh2});
}

void PayloadErbessd::dataToSignal(ErbessdData &data)
{


    if(data.type == processData){
        dataProcessToSignal(data);
    }
    else if(data.type == rawData){
        dataRawToSignal(data);
    }
    else{
        return;
    }
}


void PayloadErbessd::execute()
{


    QJsonParseError jsonError;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &jsonError);


    if (jsonDoc.isNull()) {
        return;
    }
    if (!jsonDoc.isObject()) {
        return;
    }


    QJsonObject jsonObj = jsonDoc.object();



    QStringList levelTopic = topic.split("/");



    if(levelTopic.size() < 4){
        return;
    }

    int countLevelTopic = levelTopic.size();



    ErbessdData erbessdData;


    QString stringType = levelTopic[countLevelTopic-1];
    QString idNode = levelTopic[countLevelTopic-2];
    QString idGateway = levelTopic[countLevelTopic-3];

    erbessdData.idNode = idNode;
    erbessdData.idGateway = idGateway;

    TypeData type = invMapTypeData[stringType];


    if(type == processData){
        parseProcessData(erbessdData, jsonObj);
    }
    else if(type == rawData){
        parseRawData(erbessdData, jsonObj);
    }
    else{
        return;
    }


    dataToSignal(erbessdData);

    emit finished();

}


