#ifndef MPCONF_H
#define MPCONF_H
#include "QString"
#include "QStringList"

struct MPConf{
    QString hostname = "";
    int port = 0;
    QStringList topics;
};

#endif // MPCONF_H
