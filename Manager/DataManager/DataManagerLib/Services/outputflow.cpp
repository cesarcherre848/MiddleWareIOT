#include "outputflow.h"
#include <sstream>

OutputFlow::OutputFlow(const QMap<QString, AssignedComponent> &newAssignedComponent, QSettings &_settings)
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
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/MQTTPublish/BuildGCC11/debug");
        addDirectoryPlugins("/home/cesarcherre/Projects/MiddleWareIOT/Plugins/Interface/Plugins/Save2DData/BuildGCC11/debug");
#endif
    }

    else{
        addDirectoryPlugins(dirRel+dirPlugins);
    }

    loadConfig();
    setAsignedComponents(newAssignedComponent);

    loadPluginIntances();


    qDebug() << "Operations Output Instances:";
    printOperationsInstances();


    mainTimeout();

/*
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("146.190.122.149"); // Solo el nombre del host o la IP, sin el número de puerto
    db.setPort(5432);
    db.setDatabaseName("TestDBData");
    db.setUserName("root");
    db.setPassword("Mc05071995..");

    //if (!db.open()) {
        //qDebug() << "Error al abrir la base de datos: " << db.lastError().text();
    //}
*/
    qDebug() << "Conexión exitosa a la base de datos";


}

OutputFlow::~OutputFlow()
{
    db.close();
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


