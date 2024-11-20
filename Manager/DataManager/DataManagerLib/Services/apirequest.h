#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "Models/Signals.h"

enum TypeRequest{
    GetAllAssignedComponents
};

class ApiRequest : public QObject
{
    Q_OBJECT
public:
    explicit ApiRequest(QObject *parent = nullptr);
    ~ApiRequest();

    void requestGetAllAssignedComponents();

private:

    void requestFinished(TypeRequest);

    void processGetAllAssignedComponents(QJsonObject data);

private:

    QNetworkAccessManager* manager = nullptr;

private slots:



public slots:

    void makeGetRequest(const QString& url, TypeRequest typeRequest);

signals:

    void updateAssignedComponents(QMap<QString, AssignedComponent>);
};

#endif // APIREQUEST_H
