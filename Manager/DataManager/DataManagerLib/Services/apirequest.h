#ifndef APIREQUEST_H
#define APIREQUEST_H
#include <QString>
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

    void setUrl_service(const QString &newUrl_service);

private:

    void requestFinished(TypeRequest);

    void processGetAllAssignedComponents(QJsonObject data);

private:

    QNetworkAccessManager* manager = nullptr;

    QString url_service = "http://localhost:2540";

private slots:



public slots:

    void makeGetRequest(const QString& url, TypeRequest typeRequest);

signals:

    void updateAssignedComponents(QMap<QString, AssignedComponent>);
};

#endif // APIREQUEST_H
