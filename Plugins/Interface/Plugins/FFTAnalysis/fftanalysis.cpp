#include "fftanalysis.h"
#include "QDebug"
#include "Constants/textMaps.h"
#include "Utils/FreqDomain.h"
#include "Utils/UnitsConvert.h"


PluginInterface *FFTAnalysis::newInstance()
{
    return new FFTAnalysis();
}

void FFTAnalysis::setSetup(const QMap<QString, QVariant> &newSetup)
{
    setup = newSetup;
    getFFTConf();
    getScalarsConf();
}

void FFTAnalysis::setAsginedSignals(const QStringList &newAsginedSignals)
{
    asginedSignals = newAsginedSignals;
}

QString FFTAnalysis::getName() const
{
    return "FFTAnalysis";
}

void FFTAnalysis::execute()
{

    if(inputDataQueue.size() <  1){
        return;
    }

    conf.mathOperation = getMathOperation(uniformInputQty, conf.outputQty);

    QList<Function> singleFunctions = {Function::FFT, Function::ESD, Function::PSD};

    if(singleFunctions.contains(conf.function)){
        computeSingleChannel();
    }


    inputDataQueue.clear();




}




void FFTAnalysis::insertData(const Signal & data)
{


    if(asginedSignals.contains(data.name)){
        if(data.type != Type::array1D){
            return;
        }

        if(inputDataQueue.size() == 0){
            uniformInputQty = data.qty;
        }
        else{
            if(uniformInputQty != data.qty){
                uniformInputQty = PhysicalQty::other;
            }
        }

        inputDataQueue.enqueue(data);
    }
}



void FFTAnalysis::getFFTConf()
{
    if(setup.contains("blockSize")){
        conf.blockSize = setup["blockSize"].toInt();

    }

    if(setup.contains("numAvg")){
        conf.numAvg = setup["numAvg"].toInt();
    }

    if(setup.contains("avg")){
        conf.avg = invMapAverage[setup["avg"].toString()];
    }

    if(setup.contains("scale")){
        conf.scale = invMapScale[setup["scale"].toString()];
    }

    if(setup.contains("ampFormat")){
        conf.ampFormat = invMapAmpFormat[setup["ampFormat"].toString()];
    }

    if(setup.contains("window")){
        conf.window = invMapWindow[setup["window"].toString()];
    }

    if(setup.contains("unitFreq")){
        conf.unitFreq = invMapUnitFreq[setup["unitFreq"].toString()];
    }

    if(setup.contains("function")){
        conf.function = invMapFunction[setup["function"].toString()];
    }

    if(setup.contains("outputType")){
        conf.outputType = invMapOutputType[setup["outputType"].toString()];
    }

    if(setup.contains("isDCFilter")){
        conf.isDCFilter = setup["isDCFilter"].toBool();
    }

    if(setup.contains("fcDCFilter")){
        conf.fcDCFilter = setup["fcDCFilter"].toDouble();
    }


    conf.outputQty = PhysicalQty::velocity;

    qDebug() << "blockSize" << conf.blockSize;
    qDebug() << "numAvg" << conf.numAvg;
    //qDebug() << "avg" << conf.avg;
    //qDebug() << "blockSize" << conf.blockSize;
    //qDebug() << "blockSize" << conf.blockSize;
}

void FFTAnalysis::getScalarsConf()
{
    if(setup.contains("isFullRange")){
        scalarsConf.isFullRange = setup["isFullRange"].toBool();
    }


    CustomRange customRange;
    customRange.min = 1.;
    customRange.max = 500.;


    //scalarsConf.customRanges << customRange;

    customRange.min = 40.0;
    customRange.max = 125;

    //scalarsConf.customRanges << customRange;

}

void FFTAnalysis::computeSingleChannel()
{

    QQueue<Signal> singleChannelQueue;
    int itemsToProcess = inputDataQueue.size();
    for (int i = 0; i < itemsToProcess; i++) {
        Signal currentData = inputDataQueue.dequeue();
        computeSingleFunction(currentData, singleChannelQueue);
    }

    int items = singleChannelQueue.size();
    for (int i = 0; i < items; i++) {
        Signal signal = singleChannelQueue.dequeue();
        emit processedData(signal);
    }

    singleChannelQueue.clear();
}

void FFTAnalysis::computeSingleFunction(Signal data, QQueue<Signal>& queue)
{

    std::vector<double> dataTime = data.array1D;
    double deltaTime = 1./data.rate;

    if(dataTime.empty()){
        return;
    }

    if(conf.blockSize > (int)dataTime.size()){
        return;
    }


    std::vector<double> real;
    std::vector<double> imag;
    std::vector<double> mag;
    std::vector<double> phase;
    double deltaFreq;

    Function function = conf.function;
    Unit outputUnit = Unit::mm_s;
    UnitOperation unitOperation = getUnitOperation(invMapUnit[data.unit], outputUnit);

    switch (function) {
    case Function::FFT:
        computeFFTAvg(dataTime, deltaTime, deltaFreq, conf, unitOperation, real, imag, mag, phase);
        break;
    }

    int size = real.size();

    if( size == 0){
        return;
    }


    if(conf.outputType == OutputType::Magnitude){
        Signal dataMag;
        dataMag.name = QString("%1_%2_Magnitude_%3").arg(data.name)
                           .arg("FFT")
                           .arg(mapAmpFormat[conf.ampFormat]);
        dataMag.idNode = data.idNode;
        dataMag.channel = data.channel;
        dataMag.type = Type::array2D;
        dataMag.unit = mapUnit[outputUnit];
        dataMag.timestamp = data.timestamp;
        dataMag.rate = deltaFreq;
        std::vector<std::vector<double>> array2D (2, std::vector<double>(mag.size()));
        array2D[0] = getFrequencyVector(0., size, deltaFreq);
        array2D[1] = mag;

        dataMag.array2D = array2D;




        queue.enqueue(dataMag);
    }

    if(scalarsConf.isFullRange){
        Signal dataFullRange;
        dataFullRange.name = QString("%1_%2_Full_Range_%3").arg(data.name)
                                 .arg("FFT")
                                 .arg(mapAmpFormat[conf.ampFormat]);
        dataFullRange.idNode = data.idNode;
        dataFullRange.channel = data.channel;
        dataFullRange.value = computeModule(mag);
        dataFullRange.type = Type::value;
        dataFullRange.unit = mapUnit[outputUnit];
        dataFullRange.timestamp = data.timestamp;


        //qDebug()  << dataFullRange;

        queue.enqueue(dataFullRange);
    }



    foreach(CustomRange customRange, scalarsConf.customRanges){
        double min = customRange.min;
        double max = customRange.max;

        if(max < min){
            continue;
        }

        int index_min = std::floor(min/deltaFreq);
        if(index_min < 0){
            index_min = 0;
        }

        int index_max = std::ceil(max/deltaFreq);
        if(index_max > size - 1){
            index_max = size - 1;
        }


        std::vector<double> extractedMag;

        std::copy(mag.begin() + index_min, mag.begin() + index_max + 1, std::back_inserter(extractedMag));

        double value = computeModule(extractedMag);

        Signal dataCustomRange;
        dataCustomRange.name = QString("%1_%2_%3_Custom_Range_[%4,%5]_%6").arg(data.name)
                                   .arg("FFT")
                                   .arg(mapMathOperation[conf.mathOperation])
                                   .arg(QString::number(min, 'f', 1)).arg(QString::number(max, 'f', 1))
                                   .arg(mapAmpFormat[conf.ampFormat]);
        dataCustomRange.idNode = data.idNode;
        dataCustomRange.channel = data.channel;
        dataCustomRange.value = value;
        dataCustomRange.type = Type::value;
        dataCustomRange.unit = mapUnit[outputUnit];
        dataCustomRange.timestamp = data.timestamp;


        //qDebug() << dataCustomRange;

        queue.enqueue(dataCustomRange);
    }





    //qDebug() << deltaFreq << mag;


}



