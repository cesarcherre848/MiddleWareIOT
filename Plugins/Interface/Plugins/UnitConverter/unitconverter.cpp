#include "unitconverter.h"
#include "QDebug"
#include "Constants/flowMaps.h"
#include "Utils/TimeDomain.h"
//#include "Constants/textMaps.h"
//#include "Utils/FreqDomain.h"
//#include "Utils/UnitsConvert.h"


PluginInterface *UnitConverter::newInstance()
{
    return new UnitConverter();
}

void UnitConverter::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getUCConf();

}

void UnitConverter::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;
}

QString UnitConverter::getName() const
{
    return "UnitConverter";
}

void UnitConverter::execute()
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


void UnitConverter::insertData(const Signal & data)
{



    if(asginedSignals.contains(data.name)){
        if(data.type != Type::array1D){
            return;
        }
        inputDataQueue.enqueue(data);
    }
}

void UnitConverter::setAlias(const QString &newAlias)
{

}

void UnitConverter::getUCConf()
{
    conf.HP_bt = 2.;
    conf.HP_fc = 5.;
    conf.outputUnit = "mm/s";
}

void UnitConverter::computeOperation(Signal data, QQueue<Signal> &queue)
{
    std::vector<double> dataTimeWaveform = data.array1D;
    double deltaTime = 1./data.rate;
    double rate = data.rate;

    if(dataTimeWaveform.empty()){
        return;
    }

    QString inputUnit = data.unit;
    QString outputUnit = conf.outputUnit;

    if(outputUnit.isEmpty()){
        return;
    }

    QString mapUnitConverter = QString("%1_%2").arg(inputUnit).arg(outputUnit);

    //flowOperation flowOp = mapFlowOperations[mapUnitConverter];
    double aCoeff = 9810.;
    double bCoeff = 0.;
    MathOperation mathOp = MathOperation::Integral;

    std::vector<double> coeffFIR;
    std::vector<double> outDataTimeWaveform;



    switch (mathOp) {

    case MathOperation::Integral:

        if(conf.HP_bt != 0. &&  conf.HP_fc != 0. ){
            computeIntegralHPFilter(conf.HP_fc, conf.HP_bt, rate, coeffFIR);
        }
        outDataTimeWaveform = computeTWIntegral(dataTimeWaveform, deltaTime, coeffFIR, aCoeff, bCoeff);

        break;
    default:

        break;
    }

    if(outDataTimeWaveform.empty()){
        return;
    }

    Signal dataOut;

    dataOut.name = QString("%1_%2").arg(data.name).arg("UC");

    dataOut.idNode = data.idNode;
    dataOut.channel = data.channel;
    dataOut.type = Type::array1D;
    dataOut.unit = conf.outputUnit;
    dataOut.timestamp = data.timestamp;
    dataOut.rate = rate;
    dataOut.array1D = outDataTimeWaveform;

    queue.enqueue(dataOut);

}
