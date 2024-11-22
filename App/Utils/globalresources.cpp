#include "globalresources.h"
#include "QCoreApplication"

QSettings &GlobalResources::getSettings()
{
    static QSettings settings(dirSettings(), QSettings::IniFormat);
    return settings;
}

QString GlobalResources::dirSettings()
{
    return QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("settings.ini");
}

