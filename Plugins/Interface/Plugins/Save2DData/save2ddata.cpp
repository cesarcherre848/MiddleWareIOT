#include "save2ddata.h"
#include "QDebug"
#include <QVariantList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTimer>


PluginInterface *Save2DData::newInstance()
{
    return new Save2DData();
}

Save2DData::Save2DData()
{

}


Save2DData::~Save2DData()
{

}

void Save2DData::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getS2DConf();

}

void Save2DData::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;


}

QString Save2DData::getName() const
{
    return "Save2DData";
}

void Save2DData::execute()
{
    QUrl url(conf.urlUpload);


    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        QJsonObject jsonObject;
        Signal currentData = inputDataQueue.dequeue();
        applyComponentSignal(currentData);
        convertSignalToJson(currentData, jsonObject);
        postJsonAsync(url, jsonObject, this);
        //qDebug() << jsonObject;
        //completeQuery(currentData, queryString, count);

    }


    inputDataQueue.clear();
}




void Save2DData::insertData(const Signal & data)
{

    if(asginedSignals.contains(data.name)){
        QList<Type> filterTypes = {Type::array1D, Type::array2D};
        if(!filterTypes.contains(data.type)){
            return;
        }

        inputDataQueue.enqueue(data);
    }
}

void Save2DData::setAsignedComponents(const QMap<QString, AssignedComponent> &newAsignedComponents)
{
    asignedComponents = newAsignedComponents;
}

void Save2DData::setAlias(const QString &newAlias)
{
    alias = newAlias;
}


void Save2DData::getS2DConf()
{


    if(setup.contains("url")){
        QString url = setup["url"].toString();
        conf.urlUpload = url;
    }


}





void Save2DData::applyComponentSignal(Signal &signal)
{
    QString idNode = signal.idNode;
    QString& name = signal.name;
    QString channel = signal.channel;

    if(asignedComponents.contains(idNode)){
        QString idComponent = asignedComponents[idNode].id;
        QMap<QString, QString> channelMap = asignedComponents[idNode].channel;
        name = name.replace(idNode, idComponent);
        if(channelMap.contains(channel)){
            QString newChannel = channelMap[channel];
            name = name.replace(channel, newChannel);
        }
    }
}


std::vector<double> Save2DData::getXVector1DData(double init, int size, double delta)
{

    std::vector<double> output(size);

    std::generate(output.begin(), output.end(), [n = 0, delta, init]() mutable {
        return init + (n++ * delta);
    });

    return output;

}



void Save2DData::convertSignalToJson(Signal &signal, QJsonObject &jsonObject)
{

    QJsonArray xArray, yArray;
    if(signal.type == Type::array2D){
        if (signal.array2D.size() == 2) {
            xArray = QJsonArray::fromVariantList(
                QList<QVariant>(signal.array2D[0].begin(), signal.array2D[0].end())
                );
            yArray = QJsonArray::fromVariantList(
                QList<QVariant>(signal.array2D[1].begin(), signal.array2D[1].end())
                );
        }
        else{
            return;
        }
    }
    else if(signal.type == Type::array1D){

        std::vector<double> timeVector = getXVector1DData(0., signal.array1D.size(), 1./signal.rate);

        xArray = QJsonArray::fromVariantList(
            QList<QVariant>(timeVector.begin(), timeVector.end())
            );

        yArray = QJsonArray::fromVariantList(
            QList<QVariant>(signal.array1D.begin(), signal.array1D.end())
            );

        //jsonObject["x_unit"] = "Sec";
    }

    jsonObject["measurement"] = signal.name;

    if (signal.timestamp.isValid()) {
        double timestampWithDecimals = signal.timestamp.toMSecsSinceEpoch() / 1000.0;
        jsonObject["timestamp"] = timestampWithDecimals;
    } else {
        jsonObject["timestamp"] = 0;
    }


    jsonObject["x"] = xArray;
    jsonObject["y"] = yArray;
    jsonObject["y_unit"] = signal.unit;
    jsonObject["x_unit"] = "undefinded";
}

void Save2DData::postJsonAsync(const QUrl &url, const QJsonObject &jsonObject, QObject *parent)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonArray jsonArray;
    jsonArray.append(jsonObject);

    QByteArray jsonData = QJsonDocument(jsonArray).toJson();
    QNetworkReply *reply = manager->post(request, jsonData);

    // Configurar un temporizador como hijo de reply
    QTimer *timeoutTimer = new QTimer(reply); // Ahora el temporizador es hijo de reply
    timeoutTimer->setSingleShot(true);

    // Conectar timeout del temporizador
    QObject::connect(timeoutTimer, &QTimer::timeout, reply, [reply]() {
        if (reply->isRunning()) {
            reply->abort(); // Cancelar la solicitud
            qDebug() << "Request timed out.";
        }
    });

    // Conectar la señal finished de reply
    QObject::connect(reply, &QNetworkReply::finished, reply, [reply, manager]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Request failed. Error:" << reply->errorString();
        }

        reply->deleteLater(); // Liberar memoria de reply
        manager->deleteLater(); // Liberar el administrador
    });

    // Iniciar el temporizador
    timeoutTimer->start(20000); // Tiempo de espera de 10 segundos

}

