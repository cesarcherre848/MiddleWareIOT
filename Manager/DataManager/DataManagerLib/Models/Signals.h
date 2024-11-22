#ifndef SIGNALS_H
#define SIGNALS_H
#include <vector>
#include "QDateTime"
#include <algorithm>
#include "QDebug"
#include <iostream>
#include <QUuid>

enum Type{
   value,
   array1D,
   array2D,
};

enum PhysicalQty{
    other,
    voltage,
    current,
    temperature,
    acceleration,
    velocity,
    displacement,
    pressure,
    power,
};

enum AmplitudeFormat{
    none,
    rms,
    pk_pk,
    pk,
};


struct AssignedComponent{
    QString id;
    QMap<QString, QString> channel;
};


struct Signal{

    QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString name;
    QString idNode;
    QString channel;
    Type type;
    double value;
    std::vector<double> array1D;
    std::vector<std::vector<double>> array2D;
    double rate = -1.;
    QDateTime timestamp;
    QString unit;
    PhysicalQty qty;
    AmplitudeFormat ampFormat;
    bool isNew;

};


inline QDebug operator<<(QDebug dbg, const Signal &s) {
    if(s.type == value){
        dbg.nospace() << qPrintable(QString("%1  %2  %3 %4 %5").arg(s.timestamp.toString("dd-MM-yyyy hh:mm:ss")).arg(s.name).arg(s.value).arg(s.unit).arg(""));
    }

    else if(s.type == array1D){

        double min = *std::min_element(s.array1D.begin(), s.array1D.end());
        double max = *std::max_element(s.array1D.begin(), s.array1D.end());

        dbg.nospace() << qPrintable(QString("%1  %2  Channel Size(%3) - Min: %4 Max: %5 Rate: %6 Hz %7 %8").arg(s.timestamp.toString("dd-MM-yyyy hh:mm:ss"))

                                        .arg(s.name)

                             .arg(s.array1D.size())
                             .arg(min).arg(max)
                             .arg(s.rate)
                             .arg(s.unit)
                             .arg(""));
    }

    else if(s.type == array2D){
        double min = *std::min_element(s.array2D[1].begin(), s.array2D[1].end());
        double max = *std::max_element(s.array2D[1].begin(), s.array2D[1].end());

        int size = s.array2D[0].size();

        dbg.nospace() << qPrintable(QString("%1  %2  Channel Size(2x%3) - Min: %4 Max: %5 Rate: %6 Hz %7 %8").arg(s.timestamp.toString("dd-MM-yyyy hh:mm:ss"))

                                        .arg(s.name)

                                        .arg(size)
                                        .arg(min).arg(max)
                                        .arg(s.rate)
                                        .arg(s.unit)
                                        .arg(""));
    }

    return dbg.space();
}

#endif // SIGNALS_H
