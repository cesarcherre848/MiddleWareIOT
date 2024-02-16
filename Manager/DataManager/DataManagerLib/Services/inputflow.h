#ifndef INPUTFLOW_H
#define INPUTFLOW_H

#include <QObject>
#include "Models/Signals.h"
#include "QMutex"
#include "QQueue"
#include "QTimer"

class InputFlow : public QObject
{
    Q_OBJECT
public:
    explicit InputFlow(QQueue<Signal>& inputDataQueue);
    ~InputFlow();

    void setCleanTimeout(bool newCleanTimeout);

    void setMsVerify(int newMsVerify);

    void setLimitSize(int newLimitSize);

signals:

    void newInputData(const Signal&);

public slots:

    void insertData(const Signal&);


private:

    void verifySizeInputQueue();

    void mainTimeout();

private:

    QQueue<Signal>& inputDataQueue_;

    QTimer* sizeCheckTimer;
    bool cleanTimeout = false;
    int msVerify = 10000;
    int limitSize = 20;

    QTimer* timer;

public:

    QMutex mutex;





};

#endif // INPUTFLOW_H
