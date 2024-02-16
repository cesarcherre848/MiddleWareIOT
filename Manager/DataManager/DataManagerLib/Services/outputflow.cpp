#include "outputflow.h"
#include <sstream>

OutputFlow::OutputFlow(const QMap<QString, AssignedComponent> &newAssignedComponent)
{

#ifdef QT_DEBUG


    directoryPlugins << "D:/Proyectos/Health Vibration Monitoring/MiddleWareIOT/Plugins/Interface/Plugins/MQTTPublish/BuildMingw8164/debug";



#else \
    // Código para compilación en modo Release
#endif


    setAsignedComponents(newAssignedComponent);

    loadOperations();
    loadPluginIntances();
    //loadOperaitonInstances();

    qDebug() << "Operations Output Instances:" << operationsInstances;


    mainTimeout();


    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("146.190.122.149"); // Solo el nombre del host o la IP, sin el número de puerto
    db.setPort(5432);
    db.setDatabaseName("TestDBData");
    db.setUserName("root");
    db.setPassword("Mc05071995..");

    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos: " << db.lastError().text();
    }

    qDebug() << "Conexión exitosa a la base de datos";


}

OutputFlow::~OutputFlow()
{
    if(timer){
        delete timer;
    }

    db.close();
}


void OutputFlow::mainTimeout()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OutputFlow::execute);
    timer->start(2000);


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

void OutputFlow::loadOperations()
{
    Operation MQTTPublish;
    MQTTPublish.name = "MQTTPublish";
    //fft1.assignedSignalName = {"189301635_Acceleration_ch0", "189301635_Acceleration_ch1", "189301635_Acceleration_ch2"};

    MQTTPublish.assignedSignalName = {
        "189301637_ERB_Temperature",
        "189301637_ERB_Battery",
        "189301637_ERB_Velocity_ch0_RMS",
        "189301637_ERB_Velocity_ch1_RMS",
        "189301637_ERB_Velocity_ch2_RMS"
        //"189301637_Accelerometer_ch0"
        //"189301637_Accelerometer_ch1",
        //"189301637_Accelerometer_ch2",
    };

    operations << MQTTPublish;
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

void OutputFlow::execute()
{



    QSqlQuery query(db);

    // Comenzar la transacción



    QString queryString = "INSERT INTO \"Test\" (id, measurement, \"timestamp\", arrayx, arrayy) VALUES ";

    int items = outputDataQueue.size();
    int count = 0;
    for (int i = 0; i < items; ++i) {
        mutex.lock();
        Signal currentData = outputDataQueue.dequeue();
        insertDatatoOperation(currentData);
        mutex.unlock();


        applyComponentSignal(currentData);
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


        qDebug() << currentData;
    }

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

    executeAllOperations();



}

void OutputFlow::insertData(const Signal & signal)
{
    mutex.lock();
    outputDataQueue.enqueue(signal);
    mutex.unlock();
}
