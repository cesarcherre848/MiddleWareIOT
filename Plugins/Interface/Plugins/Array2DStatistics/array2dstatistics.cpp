#include "array2dstatistics.h"
#include "QDebug"
#include <algorithm>
#include "Utils/Array2DDomain.h""
#include "Constants/textMaps.h"

//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *Array2DStatistics::newInstance()
{
    return new Array2DStatistics();
}

void Array2DStatistics::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getA2DSConf();


}

void Array2DStatistics::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;



}


void Array2DStatistics::setAlias(const QString &newAlias)
{

    alias = newAlias;
    qDebug() << alias;
}


QString Array2DStatistics::getName() const
{
    return "Array2DStatistics";
}

void Array2DStatistics::execute()
{



    if(inputDataQueue.size() <  1){
        return;
    }


    QQueue<Signal> outChannelQueue;
    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        Signal currentData = inputDataQueue.dequeue();
        computeOperation(currentData, outChannelQueue);
        //computeSingleFunction(currentData, singleChannelQueue);
    }


    int items = outChannelQueue.size();
    for (int i = 0; i < items; i++) {
        Signal signal = outChannelQueue.dequeue();
        emit processedData(signal);
    }

    outChannelQueue.clear();



    inputDataQueue.clear();

}


void Array2DStatistics::insertData(const Signal & data)
{

    //qDebug() << "insert data" << data.name << asginedSignals;

    if(asginedSignals.contains(data.name)){
        //qDebug() << data.name << data.type;

        if(data.type != Type::array2D){
            return;
        }

        inputDataQueue.enqueue(data);
    }
}


void Array2DStatistics::getA2DSConf()
{
    if(setup.contains("functions")){


        QVariantList listFunctions = setup["functions"].toList();
        foreach (QVariant item, listFunctions) {
            Function function;
            QMap functionMap = item.toMap();
            if(functionMap.contains("searchAxis")){
                function.searchAxis = functionMap["searchAxis"].toString();
            }
            if(functionMap.contains("operation")){
                function.operation = invMapOperation[functionMap["operation"].toString()];
            }
            if(functionMap.contains("alias")){
                function.alias = functionMap["alias"].toString();
            }
            if(functionMap.contains("range")){
                QList<QVariant> rangeList = functionMap["range"].toList();
                QVector<double> rangeVector(2);
                std::transform(rangeList.begin(), rangeList.end(), rangeVector.begin(),
                               [](const QVariant &item) { return item.toDouble(); });

                function.range = rangeVector;
            }

            conf.functions << function;
        }

    }
}



void Array2DStatistics::computeOperation(Signal data, QQueue<Signal> &queue)
{

    //qDebug() <<  "compute operation";

    std::vector<std::vector<double>> data2DArray = data.array2D;

    if(data2DArray.empty()){
        return;
    }

    if(data2DArray.size() != 2){
        return;
    }


    QList<Function> functions = conf.functions;

    QString searchAxis = "";
    QString opAlias = "";
    QVector<double> range(2);

    foreach (Function function, functions) {
        searchAxis = function.searchAxis;
        Operation operation = function.operation;
        range = function.range;
        opAlias = function.alias;
        double value = 0.;

        switch (operation) {
        case Operation::Max:
            value = computeMax(data2DArray, searchAxis, range);
            break;
        }

        Signal dataOut;
        dataOut.name = QString("%1_%2_%3").arg(data.name).arg(alias).arg(opAlias);
        dataOut.idNode = data.idNode;
        dataOut.channel = data.channel;
        dataOut.type = Type::value;
        dataOut.value = value;

        dataOut.unit = data.unit;

        dataOut.timestamp = data.timestamp;

        queue.enqueue(dataOut);

    }
    /*

    QList<Function> functions = conf.functions;

    for (int i = 0; i < functions.size(); ++i) {
        Function function = functions[i];
        double value = 0.;
        QString subProcess = mapFunction[function];

        switch (function) {
        case Function::RMS:
            value = computeRMS(dataTimeWaveform);
            break;
        case Function::Skewness:
            value = computeSkewness(dataTimeWaveform);
            break;
        case Function::Kurtosis:
            value = computeKurtosis(dataTimeWaveform);
            break;
        case Function::Crest_Factor:
            value = computeCrestFactor(dataTimeWaveform);
            break;
        case Function::Peak:
            value = computePeak(dataTimeWaveform);
            break;
        case Function::Peak_Peak:
            value = computePeakToPeak(dataTimeWaveform);
            break;
        }

        Signal dataOut;
        dataOut.name = QString("%1_%2_%3").arg(data.name).arg("BS").arg(subProcess);
        dataOut.idNode = data.idNode;
        dataOut.channel = data.channel;
        dataOut.type = Type::value;
        dataOut.value = value;

        dataOut.unit = data.unit;

        dataOut.timestamp = data.timestamp;

        queue.enqueue(dataOut);

    }
    */



}

