#ifndef S2DCONF_H
#define S2DCONF_H
#include "QString"

struct S2DConf{
    QString hostname = "";
    int port = 0;
    QString database = "";
    QString username = "";
    QString password = "";
    int reconnectionAttempts = 1;
    int reconnectionTimeout = 0;
};


#endif // S2DCONF_H
