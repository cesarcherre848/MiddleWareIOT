#include "PayloadMilesight.h"
#include "QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
//#include "Models/ErbessdData.h"
//#include "Constants/textMaps.h"
#include "QDateTime"
#include "QTimeZone"


PayloadMilesight::PayloadMilesight(QObject *parent)
    : MQTTParser{parent}
{


}

PayloadMilesight::~PayloadMilesight()
{

}

void PayloadMilesight::setPayLoad(const QByteArray &byteArray, QString topic)
{

    this->byteArray = byteArray;
    this->topic = topic;


}


void PayloadMilesight::parseProcessData(MilesightData &data, const QJsonObject &json)
{

    const QJsonValue &devEUIValue = json["devEUI"];

    if(devEUIValue.isString()){
        data.devEUI = devEUIValue.toString();
    }

    const QJsonValue &deviceNameValue = json["deviceName"];

    if(deviceNameValue.isString()){
        data.deviceName = deviceNameValue.toString();
    }

    const QJsonValue &timezoneValue = json["timezone"];

    if(timezoneValue.isString()){
        data.timezone = timezoneValue.toString();
    }


    const QJsonValue &timestampValue = json["timestamp"];
    if(timestampValue.isDouble()){

        data.timestamp = QDateTime::fromSecsSinceEpoch(timestampValue.toInt(), QTimeZone(data.timezone.toUtf8()));
    }


    if (json.contains("modbus_chnn_1")){
        const QJsonValue &modbusChnn1Value = json["modbus_chnn_1"];

        if(modbusChnn1Value.isDouble()){
            data.modbusChs.insert("ch1", modbusChnn1Value.toDouble());
        }
    }



    if (json.contains("modbus_chnn_2")){
        const QJsonValue &modbusChnn2Value = json["modbus_chnn_2"];

        if(modbusChnn2Value.isDouble()){
            data.modbusChs.insert("ch2", modbusChnn2Value.toDouble());
        }
    }




    /*
    const QJsonValue &modbusChnn2Value = json["modbus_chnn_2"];

    if(modbusChnn2Value.isUndefined()) {
        data.modbusChnn2 = -std::numeric_limits<double>::infinity();
    }

    else if(modbusChnn2Value.isString()){
        data.modbusChnn2 = modbusChnn2Value.toDouble();
    }
    */

}

void PayloadMilesight::dataToSignal(MilesightData &data)
{

    QList<Signal> signalList = {};

    QMap modbusChs = data.modbusChs;

    foreach (QString ch, modbusChs.keys()) {

        Signal signalCh1;
        signalCh1.name = QString("%1_MSGT_Modbus_%2").arg(data.devEUI, ch);
        signalCh1.idNode = data.devEUI;
        signalCh1.qty = PhysicalQty::other;
        signalCh1.value = modbusChs.value(ch);
        signalCh1.timestamp = data.timestamp;
        signalCh1.unit = "undefined";
        signalCh1.type = Type::value;

        signalList.append(signalCh1);
    }

    if(signalList.empty()){
        return;
    }

    emit updateSignals(signalList);

}


void PayloadMilesight::execute()
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

    MilesightData milesightData;

    parseProcessData(milesightData, jsonObj);

    dataToSignal(milesightData);

    emit finished();

}


