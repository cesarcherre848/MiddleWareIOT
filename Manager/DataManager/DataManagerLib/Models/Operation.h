#ifndef OPERATION_H
#define OPERATION_H
#include "QString"
#include "QStringList"
#include "QMap"
#include "QVariant"

struct Operation{

    QString name;
    QString alias;
    QStringList assignedSignalName;
    QMap<QString, QVariant> setup;

};

#endif // OPERATION_H
