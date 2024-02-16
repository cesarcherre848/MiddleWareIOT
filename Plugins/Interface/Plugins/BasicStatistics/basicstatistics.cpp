#include "basicstatistics.h"
#include "QDebug"

//#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *BasicStatistics::newInstance()
{
    return new BasicStatistics();
}

void BasicStatistics::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;


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
        //computeOperation(currentData, outChannelQueue);
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


void BasicStatistics::computeOperation(Signal data, QQueue<Signal> &queue)
{
    std::vector<double> dataTimeWaveform = data.array1D;
    //double deltaTime = 1./data.rate;
    //double rate = data.rate;

    if(dataTimeWaveform.empty()){
        return;
    }




}

