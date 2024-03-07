#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#include "Models/BSConf.h"

const QMap<Function, QString> mapFunction = {
    {Function::RMS, "RMS"},
    {Function::Peak, "Peak"},
    {Function::Peak_Peak, "Peak Peak"},
    {Function::Crest_Factor, "Crest Factor"},
    {Function::Kurtosis, "Kurtosis"},
    {Function::Skewness, "Skewness"},
};

const QMap<QString, Function> invMapFunction = {
    {"RMS", Function::RMS},
    {"Peak", Function::Peak},
    {"Peak Peak", Function::Peak_Peak},
    {"Crest Factor", Function::Crest_Factor},
    {"Kurtosis", Function::Kurtosis},
    {"Skewness", Function::Skewness},
};


#endif // TEXTMAPS_H
