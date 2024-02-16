#ifndef TEXTMAPS_H
#define TEXTMAPS_H
#include "Models/ErbessdData.h"

const QMap<TypeData, QString> mapTypeData = {

    {TypeData::processData, "stateupdate"},
    {TypeData::rawData, "collection"},
};


const QMap<QString, TypeData> invMapTypeData = {

    {"stateupdate", TypeData::processData},
    {"collection", TypeData::rawData},
};





#endif // TEXTMAPS_H
