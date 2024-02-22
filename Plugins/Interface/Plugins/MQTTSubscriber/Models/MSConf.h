#ifndef MSCONF_H
#define MSCONF_H
#include "QString"
#include "QMap"
#include "QStringList"

enum TypeParser{
    ERB,
    DW
};

struct MSConf {
    QString hostname = "";
    int port  = 0;
    QMap<QString, QStringList> parserTopics;
};

#endif // MSCONF_H
