#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#include "Models/A2DSConf.h"

const QMap<Operation, QString> mapOperation = {
    {Operation::Max, "Max"}
  };

const QMap<QString, Operation> invMapOperation = {
    {"Max", Operation::Max}
};


#endif // TEXTMAPS_H
