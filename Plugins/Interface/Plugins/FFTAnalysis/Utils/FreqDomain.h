#ifndef FREQDOMAIN_H
#define FREQDOMAIN_H

#include "Models/FFTConf.h"
#include <vector>
#include <cmath>
#include "fftw3.h"
#include <iterator>
#include <numeric>
#include <iostream>
#include <algorithm>


#include "TimeDomain.h"
#include "Constants/valuesMaps.h"
#include "Utils/UnitsConvert.h"
#include "Utils/TimeDomain.h"




inline std::vector<double> averageVector(std::vector<std::vector<double>> vectorData){

    if(vectorData.size() == 0){
        return {};
    }

    int rows = vectorData.size();
    int columns = vectorData[0].size();

    std::vector<double> output;
    output.resize(columns);

    for (int i = 0; i < columns; i++) {
        double sum = std::accumulate(vectorData.begin(), vectorData.end(),
                                     0.0,
                                     [i](double acc, const std::vector<double>& row) {
                                         return acc + row[i];
                                     });
        output[i] = sum / rows;
    }
    return output;
}

inline std::vector<double> weightSumVector(double weight1, const std::vector<double>& vector1, double weight2, const std::vector<double>& vector2){
    if(vector1.size() == 0 || vector2.size() == 0){
        return {};
    }

    if(vector1.size() != vector2.size()){
        return {};
    }

    std::vector<double> output;


    std::transform(vector1.begin(), vector1.end(), vector2.begin(), std::back_inserter(output),
                   [weight1 = double(weight1), weight2 = double(weight2)](double val1, double val2) {
                       return (val1*weight1) +  (val2*weight2);
                   });

    return output;
}


inline void retainMaximum(const std::vector<double>& tmpReal, const std::vector<double>& tmpImag, const std::vector<double>& real,
                          const std::vector<double>& imag, std::vector<double> &maxReal, std::vector<double> &maxImag){


    if(tmpReal.empty()){
        return;
    }
    if(tmpImag.empty()){
        return;
    }
    if(real.empty()){
        return;
    }
    if(imag.empty()){
        return;
    }

    int size = (int)tmpReal.size();

    if((int)tmpImag.size() != size || (int)real.size() != size || (int)imag.size() != size){
        return;
    }

    maxReal.resize(size);
    maxImag.resize(size);

    for (int i = 0; i < size; i++) {
        double tmpRe =  tmpReal[i];
        double tmpIm =  tmpImag[i];
        double tmpMag =  std::sqrt(tmpRe*tmpRe + tmpIm*tmpIm);

        double re =  real[i];
        double im =  imag[i];
        double mag = std::sqrt(re*re + im*im);

        if(mag > tmpMag){
            maxReal[i] = re;
            maxImag[i] = im;
        }
        else{
            maxReal[i] = tmpRe;
            maxImag[i] = tmpIm;
        }
    }

}


inline void computeFFT(std::vector<double> dataTime, double deltaTime, double &deltaFreq,
                       FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                       std::vector<double> &mag, std::vector<double> &phase, bool onlyComplex){

    int size = dataTime.size();
    if(size == 0){
        return;
    }

    computeWindow(dataTime, conf.window);

    deltaFreq = 1./(deltaTime*size);

    int indexCutoff = 0;
    if(conf.isDCFilter){
        indexCutoff = std::ceil(conf.fcDCFilter/deltaFreq)+1;
    }

    fftw_plan plan;
    fftw_complex* output;
    output = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
    plan = fftw_plan_dft_r2c_1d(size, dataTime.data(), output, FFTW_ESTIMATE | FFTW_BACKWARD);



    // Realizar la transformada FFT
    fftw_execute(plan);

    int sizeFreq = (size/2) + 1;
    real.resize(sizeFreq);
    imag.resize(sizeFreq);
    if(!onlyComplex){
        mag.resize(sizeFreq);
        phase.resize(sizeFreq);

    }

    for (int i = 0; i < sizeFreq; ++i) {
        double re, im;
        re = output[i][0];
        im = output[i][1];

        if(i < indexCutoff){
            re *= 0.;
            im *= 0.;
        }

        real[i] = re;
        imag[i] = im;
        real[i] = re*(2./size);
        imag[i] = im*(2./size);
        if(!onlyComplex){
            mag[i] = std::sqrt(re*re + im*im)*(2./size);
            phase[i] = std::atan2(im, re)*(180./M_PI);
        }
    }



    fftw_destroy_plan(plan);
    fftw_free(output);
}



inline std::vector<double> getPhaseVector(const std::vector<double>& realVector, const std::vector<double>& imagVector){
    if(realVector.size() == 0 || imagVector.size() == 0){
        return {};
    }

    if(realVector.size() != imagVector.size()){
        return {};
    }

    std::vector<double> output;


    std::transform(realVector.begin(), realVector.end(), imagVector.begin(), std::back_inserter(output),
                   [](double real, double imag) {
                       double phase = std::atan2(imag, real) * 180.0 / M_PI;
                       return phase;
                   });

    return output;
}


inline std::vector<double> getMagVector(const std::vector<double>& realVector, const std::vector<double>& imagVector){
    if(realVector.size() == 0 || imagVector.size() == 0){
        return {};
    }

    if(realVector.size() != imagVector.size()){
        return {};
    }

    std::vector<double> output;


    std::transform(realVector.begin(), realVector.end(), imagVector.begin(), std::back_inserter(output),
                   [](double real, double imag) {
                       double mag = std::sqrt(real*real + imag*imag);
                       return mag;
                   });

    return output;
}


inline double computeModule(const std::vector<double>& data){
    double sum = std::accumulate(data.begin(), data.end(), 0.0,
                                 [](double accum, double el) {
                                    return accum + (el * el);
                                 }
                                 );
    return std::sqrt(sum);
}

inline void computeMathOperation(double deltaFreq, std::vector<double> &realVector, std::vector<double> &imagVector,
                                 MathOperation mathOperation){


    if(realVector.size() == 0 || imagVector.size() == 0){
        return;
    }

    if(realVector.size() != imagVector.size()){
        return;
    }

    int size = (int)realVector.size();

    double w = 0;

    if(mathOperation == MathOperation::Integral){
        realVector[0] = 0;
        imagVector[0] = 0;
        for (int i = 1; i < size; ++i) {
            double& re = realVector[i];
            double& im = imagVector[i];
            w = i * deltaFreq * 2 * M_PI;
            re = im/w;
            im = -1.*re/w;
        }
    }


    else if(mathOperation == MathOperation::DoubleIntegral){
        realVector[0] = 0;
        imagVector[0] = 0;
        for (int i = 1; i < size; ++i) {
            double& re = realVector[i];
            double& im = imagVector[i];
            w = i * deltaFreq * 2 * M_PI;
            re = -1.*re/(w*w);
            im = -1.*im/(w*w);
        }
    }


}


inline void computeModifiers(AmpFormat ampFormat, UnitOperation unitOperation, std::vector<double> &realVector, std::vector<double> &imagVector){
    if(realVector.size() == 0 || imagVector.size() == 0){
        return;
    }

    unitOperation.a = 1.0;
    unitOperation.b = 0;

    if(realVector.size() != imagVector.size()){
        return;
    }


    int size = (int)realVector.size();

    for (int i = 1; i < size; ++i) {
        double& re = realVector[i];
        double& im = imagVector[i];
        re *= mapAmpFormatFactor[ampFormat]*unitOperation.a;
        im *= mapAmpFormatFactor[ampFormat]*unitOperation.a;
        re += unitOperation.b;
        im += unitOperation.b;
    }
}

inline void computeFFTAvg(std::vector<double> dataTime, double deltaTime, double &deltaFreq,
                          FFTConf conf, UnitOperation unitOperation,std::vector<double> &real, std::vector<double> &imag,
                          std::vector<double> &mag, std::vector<double> &phase){


    /*
    std::vector<double> coeffFIR;

    computeIntegralHPFilter(1./deltaTime, coeffFIR);

    std::vector<double> speed = computeTWIntegral(dataTime, deltaTime, coeffFIR);

    //qDebug() << speed;

    */
    std::vector<std::vector<double>> listData = splitWaveform(dataTime, conf.blockSize, conf.numAvg);
    if(listData.empty()){
        return;
    }

    for(int i=0; i < (int)listData.size(); i++){
        std::vector<double> realTmp;
        std::vector<double> imagTmp;
        std::vector<double> magTmp;
        std::vector<double> phaseTmp;

        computeFFT(listData[i], deltaTime, deltaFreq, conf, realTmp, imagTmp, magTmp, phaseTmp, true);

        if(i == 0){
            real.resize(realTmp.size());
            imag.resize(imagTmp.size());

            real = realTmp;
            imag = imagTmp;
        }

        else{

            if(conf.avg == Average::Linear){
                std::vector<double> prevReal = real;
                std::vector<double> prevImag = imag;
                double weight1 = 1./(i+1);
                double weight2 = 1. - weight1;
                real = weightSumVector(weight1, realTmp, weight2, real);
                imag = weightSumVector(weight1, imagTmp, weight2, imag);
            }

            else if(conf.avg == Average::PeakHold){
                std::vector<double> prevReal = real;
                std::vector<double> prevImag = imag;

                retainMaximum(realTmp, imagTmp, prevReal, prevImag, real, imag);
            }

        }
    }

    //computeModifiers(conf.ampFormat, unitOperation, real, imag);

    /*
    if(conf.mathOperation != MathOperation::None){
        computeMathOperation(deltaFreq, real, imag, conf.mathOperation);
    }
*/





    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);


}


inline void computeAutoSpectrumAvg(std::vector<double> dataTime, double deltaTime, double &deltaFreq,
                                   FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                                   std::vector<double> &mag, std::vector<double> &phase){


    std::vector<std::vector<double>> listData = splitWaveform(dataTime, conf.blockSize, conf.numAvg);
    if(listData.empty()){
        return;
    }

    for(int i=0; i < (int)listData.size(); i++){
        std::vector<double> realTmp;
        std::vector<double> imagTmp;
        std::vector<double> magTmp;
        std::vector<double> phaseTmp;

        computeFFT(listData[i], deltaTime, deltaFreq, conf, realTmp, imagTmp, magTmp, phaseTmp, false);

        std::transform(magTmp.begin(), magTmp.end(), magTmp.begin(),
                       [](double mg) {
                           return mg*mg;
                       });

        realTmp = magTmp;
        imagTmp.assign(realTmp.size(), 0.);

        if(i == 0){
            real.resize(realTmp.size());
            imag.resize(imagTmp.size());

            real = realTmp;
            imag = imagTmp;
        }

        else{

            if(conf.avg == Average::Linear){
                std::vector<double> prevReal = real;
                double weight1 = 1./(i+1);
                double weight2 = 1. - weight1;
                real = weightSumVector(weight1, realTmp, weight2, real);
            }

            else if(conf.avg == Average::PeakHold){
                std::vector<double> prevReal = real;
                std::vector<double> prevImag = imag;

                retainMaximum(realTmp, imagTmp, prevReal, prevImag, real, imag);
            }

        }
    }


    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);
}



inline void computePSDAvg(std::vector<double> dataTime, double deltaTime, double &deltaFreq,
                          FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                          std::vector<double> &mag, std::vector<double> &phase){




    computeAutoSpectrumAvg(dataTime, deltaTime, deltaFreq, conf, real, imag, mag, phase);

    double bw = deltaFreq*mapWindowFactor[conf.window];


    std::transform(real.begin(), real.end(), real.begin(), [bw](double re){
        return re*(1/bw);
    });
    mag = real;

}

inline void computeESDAvg(std::vector<double> dataTime, double deltaTime, double &deltaFreq,
                          FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                          std::vector<double> &mag, std::vector<double> &phase){

    computePSDAvg(dataTime, deltaTime, deltaFreq, conf, real, imag, mag, phase);

    std::transform(real.begin(), real.end(), real.begin(), [blockSamples = int(conf.blockSize), dt = double(deltaTime)](double re){
        return re*blockSamples*dt;
    });
    mag = real;
}

inline void computeCrossSpectrum(std::vector<double> dataTimeInput, std::vector<double> dataTimeOutput,double deltaTime, double &deltaFreq,
                                 FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                                 std::vector<double> &mag, std::vector<double> &phase){

    std::vector<std::vector<double>> listDataInput = splitWaveform(dataTimeInput, conf.blockSize, conf.numAvg);
    if(listDataInput.empty()){
        return;
    }

    std::vector<std::vector<double>> listDataOutput = splitWaveform(dataTimeOutput, conf.blockSize, conf.numAvg);
    if(listDataOutput.empty()){
        return;
    }

    if(listDataInput.size() != listDataOutput.size()){
        return;
    }


    for(int i=0; i < (int)listDataInput.size(); i++){
        std::vector<double> realTmpInput;
        std::vector<double> imagTmpInput;

        std::vector<double> realTmpOutput;
        std::vector<double> imagTmpOutput;

        std::vector<double> realCrossTmp;
        std::vector<double> imagCrossTmp;

        std::vector<double> magTmp;
        std::vector<double> phaseTmp;


        computeFFT(listDataInput[i], deltaTime, deltaFreq, conf, realTmpInput, imagTmpInput, magTmp, phaseTmp, true);
        computeFFT(listDataOutput[i], deltaTime, deltaFreq, conf, realTmpOutput, imagTmpOutput, magTmp, phaseTmp, true);

        double a, b, c, d;

        realCrossTmp.resize(realTmpInput.size());
        imagCrossTmp.resize(realTmpInput.size());

        for(int j = 0; j < (int)realTmpInput.size(); j++){
            a = realTmpOutput[j];
            b = imagTmpOutput[j];
            c = realTmpInput[j];
            d = -1.*imagTmpInput[j];

            realCrossTmp[j] = (a*c) - (b*d);
            imagCrossTmp[j] = (a*d) + (b*c);
        }

        if(i == 0){

            real.resize(realCrossTmp.size());
            imag.resize(imagCrossTmp.size());

            real = realCrossTmp;
            imag = imagCrossTmp;
        }

        else{
            std::vector<double> prevReal = real;
            std::vector<double> prevImag = imag;

            if(conf.avg == Average::Linear){

                double weight1 = 1./(i+1);
                double weight2 = 1. - weight1;
                real = weightSumVector(weight1, realCrossTmp, weight2, real);
                imag = weightSumVector(weight1, imagCrossTmp, weight2, imag);
            }

            else if(conf.avg == Average::PeakHold){
                retainMaximum(realCrossTmp, imagCrossTmp, prevReal, prevImag, real, imag);
            }
        }
    }

    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);
}


inline void computeTransmissibility(std::vector<double> dataTimeInput, std::vector<double> dataTimeOutput,double deltaTime, double &deltaFreq,
                                    FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                                    std::vector<double> &mag, std::vector<double> &phase){

    std::vector<double> realTmpCross;
    std::vector<double> imagTmpCross;
    std::vector<double> magTmpCross;
    std::vector<double> phaseTmpCross;

    computeCrossSpectrum(dataTimeInput, dataTimeOutput, deltaTime, deltaFreq, conf, realTmpCross, imagTmpCross, magTmpCross, phaseTmpCross);

    std::vector<double> realTmpAutoInput;
    std::vector<double> imagTmpAutoInput;
    std::vector<double> magTmpAutoInput;
    std::vector<double> phaseTmpAutoInput;

    computeAutoSpectrumAvg(dataTimeInput, deltaTime, deltaFreq, conf, realTmpAutoInput, imagTmpAutoInput, magTmpAutoInput, phaseTmpAutoInput);

    real.resize(realTmpCross.size());
    imag.resize(imagTmpCross.size());

    double a, b, c;

    for(int j = 0; j < (int)realTmpCross.size(); j++){
        a = realTmpCross[j];
        b = imagTmpCross[j];
        c = realTmpAutoInput[j];

        real[j] = a/c;
        imag[j] = b/c;
    }

    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);

}

inline void computeCoherence(std::vector<double> dataTimeInput, std::vector<double> dataTimeOutput,double deltaTime, double &deltaFreq,
                             FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                             std::vector<double> &mag, std::vector<double> &phase){

    std::vector<double> realTmpCross;
    std::vector<double> imagTmpCross;
    std::vector<double> magTmpCross;
    std::vector<double> phaseTmpCross;

    computeCrossSpectrum(dataTimeInput, dataTimeOutput, deltaTime, deltaFreq, conf, realTmpCross, imagTmpCross, magTmpCross, phaseTmpCross);

    std::vector<double> realTmpAutoInput;
    std::vector<double> imagTmpAutoInput;
    std::vector<double> magTmpAutoInput;
    std::vector<double> phaseTmpAutoInput;

    computeAutoSpectrumAvg(dataTimeInput, deltaTime, deltaFreq, conf, realTmpAutoInput, imagTmpAutoInput, magTmpAutoInput, phaseTmpAutoInput);


    std::vector<double> realTmpAutoOutput;
    std::vector<double> imagTmpAutoOutput;
    std::vector<double> magTmpAutoOutput;
    std::vector<double> phaseTmpAutoOutput;

    computeAutoSpectrumAvg(dataTimeOutput, deltaTime, deltaFreq, conf, realTmpAutoOutput, imagTmpAutoOutput, magTmpAutoOutput, phaseTmpAutoOutput);

    real.resize(realTmpCross.size());
    imag.assign(real.size(), 0.);

    double a, b, c;

    for(int j = 0; j < (int)realTmpCross.size(); j++){
        a = magTmpCross[j];
        b = realTmpAutoInput[j];
        c = realTmpAutoOutput[j];

        real[j] = a*a/(b*c);

    }

    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);

}


inline void computeODSFRF(std::vector<double> dataTimeInput, std::vector<double> dataTimeOutput,double deltaTime, double &deltaFreq,
                          FFTConf conf, std::vector<double> &real, std::vector<double> &imag,
                          std::vector<double> &mag, std::vector<double> &phase){


    std::vector<double> realTmpCross;
    std::vector<double> imagTmpCross;
    std::vector<double> magTmpCross;
    std::vector<double> phaseTmpCross;

    computeCrossSpectrum(dataTimeInput, dataTimeOutput, deltaTime, deltaFreq, conf, realTmpCross, imagTmpCross, magTmpCross, phaseTmpCross);


    std::vector<double> realTmpAutoOutput;
    std::vector<double> imagTmpAutoOutput;
    std::vector<double> magTmpAutoOutput;
    std::vector<double> phaseTmpAutoOutput;

    computeAutoSpectrumAvg(dataTimeOutput, deltaTime, deltaFreq, conf, realTmpAutoOutput, imagTmpAutoOutput, magTmpAutoOutput, phaseTmpAutoOutput);

    real.resize(realTmpCross.size());
    imag.resize(imagTmpCross.size());

    double a, b, m, c;

    for(int j = 0; j < (int)realTmpCross.size(); j++){
        m = magTmpCross[j];
        a = realTmpCross[j]/m;
        b = imagTmpCross[j]/m;
        c = std::sqrt(magTmpAutoOutput[j]);

        real[j] = a*c;
        imag[j] = b*c;

    }

    mag = getMagVector(real, imag);
    phase = getPhaseVector(real, imag);

}

inline std::vector<double> getFrequencyVector(double init, int size, double delta){
    std::vector<double> output(size);

    std::generate(output.begin(), output.end(), [n = 0, delta, init]() mutable {
        return init + (n++ * delta);
    });

    return output;
}






#endif // FREQDOMAIN_H
