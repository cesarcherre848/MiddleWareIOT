#ifndef BSCONF_H
#define BSCONF_H
#include <QList>

enum class Function{
    RMS,
    Peak,
    Peak_Peak,
    Kurtosis,
    Crest_Factor,
    Skewness
};

enum class TypeBlock{
    Time,
    Samples,
};

struct BSConf {
   QList<Function> functions;
   TypeBlock typeBlock;
   double valueBlock;
   double ov;
};



#endif // BSCONF_H
