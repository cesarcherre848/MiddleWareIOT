#include "apirequest.h"


ApiRequest::ApiRequest(QObject *parent) : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
}

ApiRequest::~ApiRequest()
{
    if(manager){
        manager->deleteLater();
    }
}

void ApiRequest::requestGetAllAssignedComponents()
{
    QString endpoint = "/devices/getall/assignedcomponents";
    QString url = url_service + endpoint;

    qDebug() << url;

    makeGetRequest(url,  TypeRequest::GetAllAssignedComponents);
}

void ApiRequest::makeGetRequest(const QString& url, TypeRequest typeRequest)
{
    if(!manager){
        return;
    }

    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [=](){
        requestFinished(typeRequest);
    });
}

void ApiRequest::requestFinished(TypeRequest typeRequest)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return;
    }


    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    if (jsonDocument.isNull()) {
        reply->deleteLater();
        return;
    }

    if(!jsonDocument.isObject()) {
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObject = jsonDocument.object();

    switch (typeRequest) {
    case TypeRequest::GetAllAssignedComponents:
        processGetAllAssignedComponents(jsonObject);
        break;
    default:
        break;
    }



    reply->deleteLater();
}

void ApiRequest::processGetAllAssignedComponents(QJsonObject data)
{
    int count = data["count"].toInt(0);

    if(count < 1){
        return;
    }


    QMap<QString, AssignedComponent> asignedComponents;

    QJsonArray dataResults = data["results"].toArray();
    for (int i = 0; i < dataResults.size(); ++i) {
        QJsonObject item = dataResults[i].toObject();
        QString idNode = item["idNode"].toString("");
        QString idComponent = item["idComponent"].toString("");

        QJsonObject chObjects = item["channelKey"].toObject();



        QMap<QString, QString> channel;

        foreach (QString key, chObjects.keys()) {
            QString valKey = chObjects[key].toString("");
            if(valKey.isEmpty()){
                continue;
            }
            channel.insert(key, valKey);
        }



        AssignedComponent value;
        value.id = idComponent;
        value.channel = channel;
        asignedComponents.insert(idNode, value);

        qDebug() << idNode << idComponent << channel;
    }


    if(asignedComponents.size() < 1){
        return;
    }

    emit updateAssignedComponents(asignedComponents);
}

void ApiRequest::setUrl_service(const QString &newUrl_service)
{
    url_service = newUrl_service;
}
