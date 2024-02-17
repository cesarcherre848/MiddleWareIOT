#include "basicstatistics.h"
#include "QDebug"

#include "Utils/TimeDomain.h"
#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *BasicStatistics::newInstance()
{
    return new BasicStatistics();
}

void BasicStatistics::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getBSConf();


}

void BasicStatistics::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;


}

QString BasicStatistics::getName() const
{
    return "BasicStatistics";
}

void BasicStatistics::execute()
{

    if(inputDataQueue.size() <  1){
        return;
    }

    /*
    conf.mathOperation = getMathOperation(uniformInputQty, conf.outputQty);

    QList<Function> singleFunctions = {Function::FFT, Function::ESD, Function::PSD};

    if(singleFunctions.contains(conf.function)){
        computeSingleChannel();
    }


    */
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


void BasicStatistics::insertData(const Signal & data)
{

    if(asginedSignals.contains(data.name)){
        if(data.type != Type::array1D){
            return;
        }

        inputDataQueue.enqueue(data);
    }
}

void BasicStatistics::getBSConf()
{
    if(setup.contains("functions")){
        QStringList strFunctions = setup["functions"].toStringList();
        foreach (QString strFunction, strFunctions) {
            conf.functions << invMapFunction[strFunction];
        }
    }
}


void BasicStatistics::computeOperation(Signal data, QQueue<Signal> &queue)
{
    std::vector<double> dataTimeWaveform = data.array1D;

    if(dataTimeWaveform.empty()){
        return;
    }

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



}

