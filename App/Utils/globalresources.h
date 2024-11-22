#ifndef GLOBALRESOURCES_H
#define GLOBALRESOURCES_H

#include <QSettings>



class GlobalResources
{
public:
    static QSettings &getSettings();

private:

    static QString dirSettings();
};

#endif // GLOBALRESOURCES_H
