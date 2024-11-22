#ifndef SCALARSCONF_H
#define SCALARSCONF_H
#include "Models/FFTConf.h"
#include "QList"


struct CustomRange {
    double min = -1.;
    double max = -1.;
    UnitFreq unitFreq = UnitFreq::Hz;
};

struct ScalarsConf {
    bool isFullRange = false;
    QList<CustomRange> customRanges;
};

#endif // SCALARSCONF_H
