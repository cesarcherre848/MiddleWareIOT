#ifndef ARRAY2DDOMAIN_H
#define ARRAY2DDOMAIN_H
#include <QString>
#include <QVector>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <QDebug>


inline int getIndexFromAxis(QString searchAxis){
    int output = 0;

    if(searchAxis == "x"){
        return 0;
    }

    else if(searchAxis == "y"){
        return 1;
    }

    return output;
}

inline int findClosestIndexfromASCOrderVector(const std::vector<double>& axisData, double a) {
    auto it = std::lower_bound(axisData.begin(), axisData.end(), a);

    if (it == axisData.end()) {
        return axisData.size() - 1;
    } else if (it == axisData.begin()) {
        return 0;
    } else {
        int idx = std::distance(axisData.begin(), it);
        if (std::abs(axisData[idx] - a) < std::abs(axisData[idx - 1] - a)) {
            return idx;
        } else {
            return idx - 1;
        }
    }
}

inline double computeMax(const std::vector<std::vector<double>>& data, QString searchAxis, QVector<double> range){
    int indexSearch = getIndexFromAxis(searchAxis);

    if(range.size() != 2){
        return -1.;
    }

    if(range[0] >= range[1]){
        return -1.;
    }

    std::vector<double> axisData = data[indexSearch];
    int indexData = 0;
    if(indexSearch == 0){
        indexData = 1;
    }
    else if(indexSearch == 1){
        indexData = 0;
    }

    std::vector<double> operationData = data[indexData];

    int minIndex = findClosestIndexfromASCOrderVector(axisData, range[0]);
    int maxIndex = findClosestIndexfromASCOrderVector(axisData, range[1]);

    if (minIndex < 0 || maxIndex >= (int)axisData.size() || minIndex > maxIndex) {
        //std::cerr << "Índices fuera de rango o inválidos\n";
        return -1.;
    }


    std::vector<double> subData(operationData.begin() + minIndex, operationData.begin() + maxIndex + 1);

    double max = *std::max_element(subData.begin(), subData.end());

    return max;

}


inline double computeModule(const std::vector<std::vector<double>>& data, QString searchAxis, QVector<double> range){
    int indexSearch = getIndexFromAxis(searchAxis);

    if(range.size() != 2){
        return -1.;
    }

    if(range[0] >= range[1]){
        return -1.;
    }

    std::vector<double> axisData = data[indexSearch];
    int indexData = 0;
    if(indexSearch == 0){
        indexData = 1;
    }
    else if(indexSearch == 1){
        indexData = 0;
    }

    std::vector<double> operationData = data[indexData];

    int minIndex = findClosestIndexfromASCOrderVector(axisData, range[0]);
    int maxIndex = findClosestIndexfromASCOrderVector(axisData, range[1]);

    if (minIndex < 0 || maxIndex >= (int)axisData.size() || minIndex > maxIndex) {
        //std::cerr << "Índices fuera de rango o inválidos\n";
        return -1.;
    }

    std::vector<double> subData(operationData.begin() + minIndex, operationData.begin() + maxIndex + 1);

    // Calcular la magnitud (suma cuadrática y raíz cuadrada) usando std::transform_reduce
    double magnitude = std::sqrt(std::accumulate(subData.begin(), subData.end(), 0.0, [](double acc, double value) {
        return acc + value * value;
    }));

    return magnitude;
}





#endif // ARRAY2DDOMAIN_H
