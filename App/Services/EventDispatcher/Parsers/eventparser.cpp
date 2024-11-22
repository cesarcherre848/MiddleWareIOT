#include "eventparser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../Constants/textMaps.h"

EventParser::EventParser(QObject *parent):
    QObject{parent}
{

}

EventParser::~EventParser()
{

}

void EventParser::setPayLoad(const QByteArray &byteArray, QString topic)
{
    this->byteArray = byteArray;
    this->topic = topic;
}

void EventParser::execute()
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


    QString type = "";
    const QJsonValue &typeValue = jsonObj["type"];
    if(typeValue.isString()){
        type = typeValue.toString();
    }

    if(type == "update"){
        ActionUpdate action =  ActionUpdate::None;

        const QJsonValue &actionValue = jsonObj["action"];
        if(actionValue.isString()){
            action = mapActionUpdate[actionValue.toString()];
        }

        if(action == ActionUpdate::None){
            emit finished();
            return;
        }

        emit updateAction(action);
    }


    emit finished();
}
