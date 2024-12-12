#include "envelope.h"
#include "QDebug"
//#include "Constants/flowMaps.h"
#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *Envelope::newInstance()
{
    return new Envelope();
}

void Envelope::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getEVConf();

}

void Envelope::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;
}

QString Envelope::getName() const
{
    return "Envelope";
}

void Envelope::execute()
{

    if(inputDataQueue.size() <  1){
        return;
    }


    QQueue<Signal> outChannelQueue;
    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        Signal currentData = inputDataQueue.dequeue();
        computeOperation(currentData, outChannelQueue);

    }


    int items = outChannelQueue.size();
    for (int i = 0; i < items; i++) {
        Signal signal = outChannelQueue.dequeue();
        emit processedData(signal);
    }

    outChannelQueue.clear();



    inputDataQueue.clear();
}


void Envelope::insertData(const Signal & data)
{



    if(asginedSignals.contains(data.name)){
        if(data.type != Type::array1D){
            return;
        }
        inputDataQueue.enqueue(data);
    }
}

void Envelope::setAlias(const QString &newAlias)
{
    alias = newAlias;
}

void Envelope::getEVConf()
{
    conf.lowerFreq = -1.;
    conf.upperFreq = -1.;
    conf.bt = 2.;

    if(setup.contains("lower_freq")){
        conf.lowerFreq = setup["lower_freq"].toDouble();
    }

    if(setup.contains("upper_freq")){
        conf.upperFreq = setup["upper_freq"].toDouble();
    }

    if(setup.contains("bt")){
        conf.bt = setup["bt"].toDouble();
    }


}

void Envelope::computeOperation(Signal data, QQueue<Signal> &queue)
{

    std::vector<double> dataTimeWaveform = data.array1D;
    double rate = data.rate;

    if(dataTimeWaveform.empty()){
        return;
    }

    double lowerFreq = conf.lowerFreq;
    double upperFreq = conf.upperFreq;
    double bt = conf.bt;

    std::vector<double> coeffFIR;
    std::vector<double> outDataTimeWaveform;



    if(lowerFreq < 0 || upperFreq < 0){
        return;
    }

    if(upperFreq < lowerFreq){
        return;
    }



    computeBandPassFilter(lowerFreq, upperFreq, bt, rate, coeffFIR);
    outDataTimeWaveform = computeTWFIRFilter(dataTimeWaveform, coeffFIR);
    outDataTimeWaveform = computeEnveloping(outDataTimeWaveform);


    if(outDataTimeWaveform.empty()){
        return;
    }

    Signal dataOut;

    dataOut.name = QString("%1_%2").arg(data.name).arg(alias);

    dataOut.idNode = data.idNode;
    dataOut.channel = data.channel;
    dataOut.type = Type::array1D;
    dataOut.unit = data.unit;
    dataOut.timestamp = data.timestamp;
    dataOut.rate = rate;
    dataOut.array1D = outDataTimeWaveform;

    queue.enqueue(dataOut);

}


