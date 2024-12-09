#ifndef TIMEDOMAIN_H
#define TIMEDOMAIN_H

#include <vector>
#include "cmath"
#include "Models/EVConf.h"
#include "QDebug"
#include "fftw3.h"
#include <iostream>

inline double computeHamming(int i, int m){
    return 0.54 - 0.46*(cos(2 * M_PI * i / m));
}

inline double sinc(int i, int m, double fcNorm){
    return sin(2 * M_PI * fcNorm * (i - (m / 2)))/(i - (m / 2));
}


inline double HiFIR(int i, int m, double k, double fcNorm, Window window){
    if(window == Window::Hamming){
        //qDebug() << sinc(i, m, fcNorm);
        return k*sinc(i,m, fcNorm)*computeHamming(i,m);
    }
    return 0.;
}

inline int factorBW(Window window){
    if(window == Window::Hamming){
        return 4;
    }
    return 1;
}

inline void computeCoeffFIR(double fs, double fc, double bt, TypeFilter typeFilter, Window window, std::vector<double>& coeff){

    int m = factorBW(window)*((int)fs/bt);
    double k = 1.;
    double fcNorm = fc/fs;
    coeff.resize(m);


    for (int i = 0; i < m; ++i) {

        coeff[i] = HiFIR(i, m, k, fcNorm, window);
    }
    coeff[(int)m/2] = k * 2 * M_PI * fcNorm;
    double accum = std::accumulate(coeff.begin(), coeff.end(), 0.0);

    std::transform(coeff.begin(), coeff.end(), coeff.begin(),
                   [accum](double &el){ return el / accum; });


    if(typeFilter == TypeFilter::LowPass){
        return;
    }

    else if(typeFilter == TypeFilter::HighPass){
        for (int i = 0; i < m; ++i) {
            coeff[i] *= -1.;
        }
        coeff[(int)m/2] += 1.;
        return;
    }
}


inline std::vector<double> convolution(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    int m = vector1.size();
    int n = vector2.size();
    int result_size = m + n - 1;
    std::vector<double>  result(result_size, 0);




    for (int i = 0; i < result_size; ++i) {
        int j_start = (i >= n - 1) ? i - (n - 1) : 0;
        int j_end = (i < m - 1) ? i : m - 1;

        result[i] = std::inner_product(vector1.begin() + j_start, vector1.begin() + j_end + 1,
                                       vector2.rbegin() + (result_size - 1 - i),
                                       result[i]);
    }

    return result;
    //std::vector<double> slideResult(result.begin() + n, result.begin() + m);
    //return slideResult;
}


inline std::vector<double> vector_elementwise_multiply(const std::vector<double> a, const std::vector<double> b)
{
    assert(a.size() == b.size());
    std::vector<double> result(a.size());
    for (int i = 0; i < (int)result.size(); ++i) {
        result[i] = a[i]*b[i];
    }
    return result;
}


std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b)
{
    int n_a = a.size();
    int n_b = b.size();
    std::vector<double> result(n_a + n_b - 1);

    for (int i = 0; i < n_a + n_b - 1; ++i) {
        double sum = 0.0;
        for (int j = 0; j <= i; ++j) {
            sum += ((j < n_a) && (i-j < n_b)) ? a[j]*b[i-j] : 0.0;
        }
        result[i] = sum;
    }
    return result;
}

std::vector<double> FFTConvolve(std::vector<double> signal1, std::vector<double> signal2) {
    int signalSize = signal1.size() + signal2.size() - 1;


    signal1.resize(signalSize, 0.);
    signal2.resize(signalSize, 0.);

    // Crear arreglos de números complejos para FFTW
    fftw_complex* in1w = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);
    fftw_complex* in2w = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);
    fftw_complex* convw = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);

    //fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);

    std::vector<double> out;
    out.resize(signalSize);

    // Crear planes de FFT para las señales de entrada y salida
    //fftw_plan plan1 = fftw_plan_dft_1d(signalSize, in1, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_plan plan1 = fftw_plan_dft_r2c_1d(signalSize, signal1.data(), in1w, FFTW_ESTIMATE);
    fftw_plan plan2 = fftw_plan_dft_r2c_1d(signalSize, signal2.data(), in2w, FFTW_ESTIMATE);

    //fftw_plan plan2 = fftw_plan_dft_1d(signalSize, in2, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //fftw_plan planInv = fftw_plan_dft_1d(signalSize, convw, out, FFTW_BACKWARD, FFTW_ESTIMATE);




    //std::copy(signal1.begin(), signal1.end(), reinterpret_cast<double*>(in1));
    //std::copy(signal2.begin(), signal2.end(), reinterpret_cast<double*>(in2));

    // Realizar la transformada de Fourier de las señales de entrada
    fftw_execute(plan1);
    fftw_execute(plan2);

    // Realizar la multiplicación en el dominio de la frecuencia


    for (int i = 0 ; i < signalSize; ++i) {
        convw[i][0] = (in1w[i][0] * in2w[i][0]) - (in1w[i][1] * in2w[i][1]); // Parte real
        convw[i][1] = (in1w[i][0] * in2w[i][1]) + (in1w[i][1] * in2w[i][0]); // Parte imaginaria
    }


    // Realizar la inversa de la transformada de Fourier

    fftw_plan planInv = fftw_plan_dft_c2r_1d(signalSize, convw, out.data(), FFTW_ESTIMATE);
    fftw_execute(planInv);

    // Almacenar el resultado de la convolución
    std::vector<double> result(signalSize);
    for (int i = 0; i < signalSize; ++i) {
        result[i] = out[i] / signalSize;
    }

    // Liberar la memoria y destruir los planes de FFTW
    fftw_destroy_plan(plan1);
    fftw_destroy_plan(plan2);
    fftw_destroy_plan(planInv);
    fftw_free(in1w);
    fftw_free(in2w);
    fftw_free(convw);
    //fftw_free(out);

    //result.resize(signal1.size());

    return result;
}

inline std::vector<double> computeEnveloping(const std::vector<double>& signal) {
    int signalSize = signal.size();

    // Crear arreglos de números complejos para FFTW
    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * signalSize);

    // Plan de FFT para transformar la señal
    fftw_plan plan = fftw_plan_dft_r2c_1d(signalSize, const_cast<double*>(signal.data()), in, FFTW_ESTIMATE);

    // Ejecutar la FFT
    fftw_execute(plan);

    // Crear la señal compleja conjugada de Hilbert
    for (int i = 1; i < signalSize / 2; ++i) {
        // Modificar la parte imaginaria para obtener la transformada de Hilbert
        out[i][0] = in[i][0];  // Mantener la parte real
        out[i][1] = -in[i][1]; // Invertir la parte imaginaria
    }
    out[0][0] = in[0][0];    // Primer punto (frecuencia cero)
    out[0][1] = 0.0;         // Parte imaginaria cero
    out[signalSize / 2][0] = in[signalSize / 2][0]; // Última frecuencia
    out[signalSize / 2][1] = 0.0;

    // Realizar la inversa de la FFT
    fftw_plan planInv = fftw_plan_dft_c2r_1d(signalSize, out, const_cast<double*>(signal.data()), FFTW_ESTIMATE);
    fftw_execute(planInv);

    // Crear la envolvente (módulo de la señal compleja)
    std::vector<double> envelop(signalSize);
    double maxSignal = 0.0;  // Para normalizar la envolvente

    // Calcular el valor máximo de la señal original para normalizar la envolvente
    for (int i = 0; i < signalSize; ++i) {
        maxSignal = std::max(maxSignal, std::abs(signal[i]));
    }

    // Calcular la envolvente normalizada
    for (int i = 0; i < signalSize; ++i) {
        envelop[i] = std::sqrt(signal[i] * signal[i] + out[i][1] * out[i][1]) / maxSignal; // Normalización
    }

    // Liberar memoria y destruir los planes FFTW
    fftw_destroy_plan(plan);
    fftw_destroy_plan(planInv);
    fftw_free(in);
    fftw_free(out);

    return envelop;
}



inline void computeIntegralTrapezoidal(const std::vector<double>& x, double dt, std::vector<double>& y) {
    int sizeX = x.size();
    y.resize(sizeX);

    if (x.size() > 1) {
        y[0] = 0.;
        for (size_t n = 1; n < x.size(); ++n) {
            y[n] = (0.5 * x[n] + 0.5 * x[n - 1])*dt + y[n - 1];
        }
    }
}


inline void computeWindow(std::vector<double> &data, Window window){

    int length = data.size();

    if(length == 0){
        return;
    }

    if(window == Window::Rectangular){
        return;
    }

    for (int i = 0; i < length; i++) {
        double windowVal = 0.0;
        if (window == Window::Hanning) {
            windowVal = (1 - cos(2 * M_PI * i / (length - 1)));
        }
        else if (window == Window::FlatTop) {
            double a0 = 1.0;
            double a1 = 1.93;
            double a2 = 1.29;
            double a3 = 0.388;
            double a4 = 0.028;
            windowVal = a0 - a1 * cos(2 * M_PI * i / (length - 1)) + a2 * cos(4 * M_PI * i / (length - 1))
                        - a3 * cos(6 * M_PI * i / (length - 1)) + a4 * cos(8 * M_PI * i / (length - 1));
        }
        data[i] *= windowVal;
    }
}




inline std::vector<std::vector<double>> splitWaveform(const std::vector<double>& waveform, int blockSize, double numAvg) {
    int length = waveform.size();

    int step = 0;
    //double ov = 0.;

    if(numAvg < 2){
        step = blockSize;
    }

    else{
        double tempOV = (length-blockSize) / ((numAvg-1)*blockSize);
        if(tempOV < 1){
            //ov = 1. - tempOV;
            step = std::floor((length-blockSize)/(numAvg-1));
        }
        else{
            step = blockSize;
        }
    }

    std::vector<std::vector<double>> sections;

    if(step < 1){
        return {};
    }

    int i = 0;
    int count = 0;
    while ((i + blockSize <= length) && count < numAvg) {

        std::vector<double> section(waveform.begin() + i, waveform.begin() + i + blockSize);
        sections.push_back(section);
        i += step;
        count++;
    }


    return sections;
}


inline std::vector<double> DCRemovalRT(std::vector<double> waveform){
    double xkminus1 = 0.;
    double ykminus1 = 0.;
    double r = 0.998;
    double xk = 0.;
    double y = 0.;

    int size = (int)waveform.size();

    std::vector<double> dataout;
    dataout.resize(size);

    for(int i=0; i < size; i++){
        xk = waveform[i];
        y = xk - xkminus1 + (r*ykminus1);
        ykminus1 = y;
        xkminus1 = xk;
        dataout[i] = y;
    }
    return dataout;
}

inline std::vector<double> computeTWIntegral(std::vector<double> waveform, double dt, std::vector<double> coeff, double a, double b){
    std::vector<double> integralWaveform;



    computeIntegralTrapezoidal(waveform, dt, integralWaveform);
    if(!coeff.empty()){
        integralWaveform = FFTConvolve(integralWaveform, coeff);
    }

    std::transform(integralWaveform.begin(), integralWaveform.end(), integralWaveform.begin(),
                   [a, b](double element) { return (element * a) + b; });

    std::vector<double> section(integralWaveform.begin() + coeff.size(), integralWaveform.begin() + waveform.size());

    return section;

}

inline void computeIntegralHPFilter(double fc, double bt, double rate, std::vector<double>& coeff){

    computeCoeffFIR(rate, fc, bt, TypeFilter::HighPass, Window::Hamming, coeff);

}

inline void computeBandPassFilter(double lower_fc, double upper_fc,
                                          double bt, double rate,
                                          std::vector<double>& bandpass_coeff){

    // Coeficientes de paso bajo (para el límite superior)
    std::vector<double> lowpass_upper_coeff;
    computeCoeffFIR(rate, upper_fc, bt, TypeFilter::LowPass, Window::Hamming, lowpass_upper_coeff);

    // Coeficientes de paso bajo (para el límite inferior)
    std::vector<double> lowpass_lower_coeff;
    computeCoeffFIR(rate, lower_fc, bt, TypeFilter::LowPass, Window::Hamming, lowpass_lower_coeff);

    // Combinar los coeficientes para crear el filtro paso de banda
    int m = lowpass_upper_coeff.size();
    bandpass_coeff.resize(m);
    for (int i = 0; i < m; ++i) {
        bandpass_coeff[i] = lowpass_upper_coeff[i] - lowpass_lower_coeff[i];
    }
}


inline std::vector<double> computeTWFIRFilter(std::vector<double> waveform, std::vector<double> coeff) {
    std::vector<double> filterWaveform;

    // Validación sin excepciones
    if (coeff.empty() || waveform.empty() || coeff.size() >= waveform.size()) {
        std::cerr << "Error: entradas inválidas. Retornando un vector vacío." << std::endl;
        return {}; // Retornar un vector vacío
    }

    // Aplicar la convolución FFT
    filterWaveform = FFTConvolve(waveform, coeff);

    // Extraer la sección útil del resultado
    std::vector<double> section(filterWaveform.begin() + coeff.size(), filterWaveform.begin() + waveform.size());

    return section;
}


#endif // TIMEDOMAIN_H
