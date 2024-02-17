#ifndef TIMEDOMAIN_H
#define TIMEDOMAIN_H
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

inline double computeRMS(const std::vector<double>& data){

    int size = data.size();
    double sum = std::accumulate(data.begin(), data.end(), 0.0,
                                          [](double acc, double value) { return acc + value * value; });

    sum = sum/size;
    double rms = std::sqrt(sum);
    return rms;
}

inline double computeMean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}


inline double computeSTD(const std::vector<double>& data, double mean) {
    double sumOfSquares = std::accumulate(data.begin(), data.end(), 0.0,
                                          [mean](double acc, double value) { return acc + std::pow(value - mean, 2); });
    return std::sqrt(sumOfSquares / data.size());
}


double computeSkewness(const std::vector<double>& data) {
    double mean = computeMean(data);
    double standardDeviation = computeSTD(data, mean);

    double sumCubedDeviations = std::accumulate(data.begin(), data.end(), 0.0,
                                                [mean](double acc, double value) { return acc + std::pow(value - mean, 3); });

    double skewness = sumCubedDeviations / (data.size() * std::pow(standardDeviation, 3));

    return skewness;
}


double computeKurtosis(const std::vector<double>& data) {
    double mean = computeMean(data);
    double standardDeviation = computeSTD(data, mean);

    double sumFourthDeviations = std::accumulate(data.begin(), data.end(), 0.0,
                                                 [mean](double acc, double value) { return acc + std::pow(value - mean, 4); });

    double kurtosis = sumFourthDeviations / (data.size() * std::pow(standardDeviation, 4));

    return kurtosis;
}


inline double computePeak(const std::vector<double>& data) {

    double peak = *std::max_element(data.begin(), data.end(),
                                         [](double a, double b) { return std::abs(a) < std::abs(b); });

    return std::abs(peak);
}


inline double computeCrestFactor(const std::vector<double>& data) {

    double peak = computePeak(data);

    double rms = computeRMS(data);

    double crestFactor = peak / rms;

    return crestFactor;
}

inline double computePeakToPeak(const std::vector<double>& data) {

    double max = *std::max_element(data.begin(), data.end());

    double min = *std::min_element(data.begin(), data.end());

    double peakToPeak = max - min;

    return peakToPeak;
}

#endif // TIMEDOMAIN_H
