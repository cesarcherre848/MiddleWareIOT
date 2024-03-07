#include "save2ddata.h"
#include "QDebug"
#include "QSqlError"
#include "QSqlQuery"
#include <sstream>
//#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *Save2DData::newInstance()
{
    return new Save2DData();
}

Save2DData::Save2DData()
{
    reconnectTimer = new QTimer(this);

}


Save2DData::~Save2DData()
{
    reconnectTimer->stop();
    reconnectTimer->deleteLater();
}

void Save2DData::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getS2DConf();
    InitTimerReconnection();
    InitDB();
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
    if(!db.isOpen()){
        if(reconnectTimer->remainingTime() < 0 && currentReconnectionAttempts < conf.reconnectionAttempts){

            reconnectTimer->start();
        }
        inputDataQueue.clear();
        return;
    }


    if(inputDataQueue.size() <  1){
        return;
    }




    QSqlQuery query(db);
    QString queryString = "INSERT INTO \"Test\" (id, measurement, \"timestamp\", arrayx, arrayy) VALUES ";
    int count = 0;


    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        Signal currentData = inputDataQueue.dequeue();
        applyComponentSignal(currentData);
        completeQuery(currentData, queryString, count);

    }

    inputDataQueue.clear();

    if(count < 1){
        return;
    }

    db.transaction();

    query.prepare(queryString);
    if (!query.exec()) {
        qWarning() << "Error in Query Insertion" << query.lastError().text();
        db.rollback(); // Revertir la transacción en caso de error
    } else {
        qInfo() << "Query Insertion Succesfully";
        query.clear();
        db.commit(); // Confirmar la transacción si la ejecución fue exitosa
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

void Save2DData::InitDB()
{

    db = QSqlDatabase::addDatabase("QPSQL");
    QString host = conf.hostname;
    int port = conf.port;
    QString name = conf.database;
    QString user = conf.username;
    QString password = conf.password;


    if( host.isEmpty() || name.isEmpty() || user.isEmpty() || password.isEmpty()){
        return;
    }


    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(name);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qWarning() << "Error open DB Manager:" << db.lastError().text();
        if(currentReconnectionAttempts > conf.reconnectionAttempts){
            currentReconnectionAttempts = conf.reconnectionAttempts;
            reconnectTimer->stop();
        }
        else{
            currentReconnectionAttempts++;
            if(reconnectTimer->remainingTime() < 0 ){
                reconnectTimer->start();
            }
        }

        return;
    }

    currentReconnectionAttempts = 0;
    reconnectTimer->stop();
    qInfo() << "Conection DB Save2D Succesfully";
}

void Save2DData::getS2DConf()
{
    if(setup.contains("hostname")){
        QString hostname = setup["hostname"].toString();
        conf.hostname = hostname;
    }
    if(setup.contains("port")){
        int port = setup["port"].toInt();
        conf.port = port;
    }
    if(setup.contains("database")){
        QString database = setup["database"].toString();
        conf.database = database;
    }
    if(setup.contains("username")){
        QString username = setup["username"].toString();
        conf.username = username;
    }
    if(setup.contains("password")){
        QString password = setup["password"].toString();
        conf.password = password;
    }
    if(setup.contains("reconnectionAttempts")){
        int reconnectionAttempts = setup["reconnectionAttempts"].toInt();
        conf.reconnectionAttempts = reconnectionAttempts;
    }
    if(setup.contains("reconnectionTimeout")){
        int reconnectionTimeout = setup["reconnectionTimeout"].toInt();
        conf.reconnectionTimeout = reconnectionTimeout;
    }


}




std::string Save2DData::vectorToText(const std::vector<double> &data)
{
    std::stringstream ss;
    ss << "{";

    if (!data.empty()) {
        ss << data[0];
        for (size_t i = 1; i < data.size(); ++i) {
            ss << ", " << data[i];
        }
    }
    ss << "}";
    return ss.str();
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

void Save2DData::completeQuery(Signal& signal, QString& queryString, int& count)
{
    QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);


    std::string arrayXText;
    std::string arrayYText;

    if(signal.type == Type::array2D){

        if(signal.array2D.empty() || signal.array2D.size() < 2){
            return;
        }

        if(signal.array2D[0].empty() || signal.array2D[0].empty() ){
            return;
        }

        arrayXText = vectorToText(signal.array2D[0]);
        arrayYText = vectorToText(signal.array2D[1]);
    }
    else if(signal.type == Type::array1D){

        arrayXText =  vectorToText(getXVector1DData(0., signal.array1D.size(), 1./signal.rate));
        arrayYText = vectorToText(signal.array1D);
    }

    if(arrayXText.empty() || arrayYText.empty()){
        return;
    }

    QString name = signal.name;
    QDateTime timestamp = signal.timestamp;
    timestamp.setTimeSpec(Qt::OffsetFromUTC);

    if (count > 0) queryString += ", ";

    queryString += "('" + id + "', '" + name + "', '" + timestamp.toString(Qt::ISODate) + "', '" + QString::fromStdString(arrayXText) + "', '" + QString::fromStdString(arrayYText) + "')";

    count++;
}

std::vector<double> Save2DData::getXVector1DData(double init, int size, double delta)
{

    std::vector<double> output(size);

    std::generate(output.begin(), output.end(), [n = 0, delta, init]() mutable {
        return init + (n++ * delta);
    });

    return output;

}

void Save2DData::InitTimerReconnection()
{
    if(!reconnectTimer){
        return;
    }
    if(conf.reconnectionTimeout <= 0){
        return;
    }
    reconnectTimer->setInterval(conf.reconnectionTimeout*1000);
    QObject::connect(reconnectTimer, &QTimer::timeout, this, &Save2DData::tryReconnect);
}

void Save2DData::tryReconnect()
{

    if(currentReconnectionAttempts <= conf.reconnectionAttempts){
        InitDB();
        return;
    }
    reconnectTimer->stop();

}



