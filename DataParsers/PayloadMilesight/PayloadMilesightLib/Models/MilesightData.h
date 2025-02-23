#ifndef MILESIGHTDATA_H
#define MILESIGHTDATA_H
#include "QString"
#include "QDateTime"



struct MilesightData{
    QString applicationID;
    QString devEUI;
    QString deviceName;

    QDateTime timestamp;
    QMap<QString, double> modbusChs;
    QString timezone;

};

/*
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
*/

#endif // MILESIGHTDATA_H
