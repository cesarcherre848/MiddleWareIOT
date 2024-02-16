#ifndef FLOWMAPS_H
#define FLOWMAPS_H
#include "QMap"
#include "Models/UCConf.h"



const QMap<QString, flowOperation> mapFlowOperations = {
    {"g_mm/s", flowOperation("g","mm/s", 9180., 0., MathOperation::Integral)},
};

#endif // FLOWMAPS_H
