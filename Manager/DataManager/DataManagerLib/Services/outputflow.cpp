#include "outputflow.h"
#include <sstream>

OutputFlow::OutputFlow(QSettings &_settings)
:BaseService{_settings}
{

    initConfig();

    const QSettings& settings = getSettings();
    QString dirPlugins = settings.value("Output/Libs", "").toString();

    if(dirPlugins.isEmpty()){

#ifdef _WIN32
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/MQTTPublish/BuildMingw8164/debug");
        addDirectoryPlugins("D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/Save2DData/BuildMingw8164/debug");
#elif __linux__
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/MQTTPublish/BuildGCC11/release");
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/Save2DData/BuildGCC11/release");
#endif
    }

    else{
        addDirectoryPlugins(dirRel+dirPlugins);
    }

    loadConfig();


}

OutputFlow::~OutputFlow()
{

}

void OutputFlow::init()
{

    loadPluginIntances();
    emit finishedLoadPlugins();

    qDebug() << "Operations Output Instances:";
    printOperationsInstances();

    mainTimeout();
}



std::string OutputFlow::vectorToText(const std::vector<double> &data)
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



void OutputFlow::applyComponentSignal(Signal &signal)
{
    QString& idNode = signal.idNode;
    QString& name = signal.name;
    QString channel = signal.channel;


    QString idComponent;
    QMap<QString, QString> channelMap;
    mutexAC.lock();
    if(asignedComponents.contains(idNode)){
        idComponent = asignedComponents[idNode].id;
        channelMap = asignedComponents[idNode].channel;
    }
    mutexAC.unlock();

    if(idComponent.isEmpty()){
        return;
    }

    if(idNode.isEmpty()){
        return;
    }


    name = name.replace(idNode, idComponent);
    if(channelMap.contains(channel)){
        QString newChannel = channelMap[channel];
        name = name.replace(channel, newChannel);
    }

    signal.idNode = idComponent;

}

void OutputFlow::initConfig()
{
    const QSettings& settings = getSettings();
    double interval = settings.value("Output/Interval", 1.).toDouble();
    dirConfig = dirRel + settings.value("Output/DirConfig", "/Config/Output").toString();
    setInterval(interval);
}

void OutputFlow::execute()
{



    QSqlQuery query(db);

    // Comenzar la transacción



    QString queryString = "INSERT INTO \"Test\" (id, measurement, \"timestamp\", arrayx, arrayy) VALUES ";

    int items = sizeDataQueue();
    int count = 0;
    for (int i = 0; i < items; ++i) {

        Signal currentData = dequeueDataQueue();
        insertDatatoOperation(currentData);



        applyComponentSignal(currentData);
        /*
        if(currentData.type == Type::array2D){


            QString id = QUuid::createUuid().toString().remove('{').remove('}');

            std::string arrayXText = vectorToText(currentData.array2D[0]);
            std::string arrayYText = vectorToText(currentData.array2D[1]);
            QString name = currentData.name;
            QDateTime timestamp = currentData.timestamp;
            timestamp.setTimeSpec(Qt::OffsetFromUTC);

            if (count > 0) queryString += ", ";

            queryString += "('" + id + "', '" + name + "', '" + timestamp.toString(Qt::ISODate) + "', '" + QString::fromStdString(arrayXText) + "', '" + QString::fromStdString(arrayYText) + "')";

            count++;
        }
        */

        qInfo() << currentData;
    }

    /*
    if(count > 0){
        db.transaction();

        query.prepare(queryString);
        if (!query.exec()) {
            qDebug() << "Error al ejecutar la consulta en lotes: " << query.lastError().text();
            db.rollback(); // Revertir la transacción en caso de error
        } else {
            qDebug() << "Inserción exitosa en lotes";
            db.commit(); // Confirmar la transacción si la ejecución fue exitosa
        }
    }
    */

    executeAllOperations();



}


