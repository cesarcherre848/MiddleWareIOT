// plugininterface.h
#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H
#include "QObject"
#include "QMap"
#include "Models/Signals.h"


class PluginInterface : public QObject {

    Q_OBJECT

public:
    virtual ~PluginInterface() {};

    virtual PluginInterface *newInstance() = 0;

    virtual void setAsginedSignals(const QStringList &newAsginedSignals) = 0;

    virtual void setSetup(const QMap<QString, QVariant> &newSetup) = 0;

    virtual void setAlias(const QString &newAlias) = 0;

    virtual QString getName() const = 0;

    virtual void execute() = 0;

    virtual void insertData(const Signal&) = 0;

    virtual void setAsignedComponents(const QMap<QString, AssignedComponent>&){};

private:


signals:


    void processedData(const Signal&);




};


#define PluginInterface_iid "com.mycompany.PluginInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGININTERFACE_H
