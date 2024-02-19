#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "QSettings"
#include <QObject>
#include "QTimer"
#include "Models/Signals.h"
#include "QMutex"
#include "QSet"
#include "QQueue"
#include "baseservice.h"

class Processor : public BaseService
{

    Q_OBJECT

public:
    //explicit Processor(QObject *parent = nullptr);
    explicit Processor(QSettings &_settings);
    ~Processor();


signals:

    void newProcessData(const Signal&);

public slots:

    void execute() override;


private:



private:

    void initConfig();
};

#endif // PROCESSOR_H
