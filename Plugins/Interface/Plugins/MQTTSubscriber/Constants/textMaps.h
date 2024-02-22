#ifndef TEXTMAPS_H
#define TEXTMAPS_H
#include "QMap"
#include "QString"
#include "Models/MSConf.h"

const QMap<QString, TypeParser> invMapTypeParser = {
    {"ERB" , TypeParser::ERB},
    {"DW" , TypeParser::DW}
};


#endif // TEXTMAPS_H
