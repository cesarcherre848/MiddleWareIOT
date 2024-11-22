#ifndef ERBESSDDATA_H
#define ERBESSDDATA_H
#include "QString"
#include "QDateTime"



enum TypeData{
    rawData,
    processData
};

struct ErbessdData{
    QString idNode;
    QString idGateway;
    QDateTime timestamp;
    float batteryLevel = -1.;
    float temperature = -1.;
    float rmsX = -1.;
    float rmsY = -1.;
    float rmsZ = -1.;
    TypeData type;
    std::vector<double> ch0;
    std::vector<double> ch1;
    std::vector<double> ch2;
    double rate = -1.;
};

inline QDebug operator<<(QDebug dbg, const ErbessdData &s) {
    dbg.nospace() << QString("Id Node: %1, Id Gateway: %2, Batt Level: %3 Volts, Temp: %4 °C, DateTime: %5, Type: %6, Channel Size: (%7, %8, %9), Rate Channel: %10 Hz")
                         .arg(s.idNode)
                         .arg(s.idGateway)
                         .arg(s.batteryLevel)
                         .arg(s.temperature)
                         .arg(s.timestamp.toString("dd-MM-yyyy hh:mm:ss"))
                         .arg(s.type)
                         .arg(s.ch0.size()).arg(s.ch1.size()).arg(s.ch2.size())
                         .arg(s.rate);
    return dbg.space();
}

#endif // ERBESSDDATA_H
