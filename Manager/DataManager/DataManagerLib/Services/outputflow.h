#ifndef OUTPUTFLOW_H
#define OUTPUTFLOW_H

#include <QObject>
#include "Models/Signals.h"
#include "QTimer"
#include "QMutex"
#include "QQueue"
#include <QtSql>
#include "baseservice.h"

class OutputFlow : public BaseService

{
    Q_OBJECT
public:
    explicit OutputFlow(const QMap<QString, AssignedComponent> &newAssignedComponent);

    ~OutputFlow();


private:

    QQueue<Signal> outputDataQueue;
    QMutex mutex;

    QTimer* timer;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");


private:

    void mainTimeout();


// just for test
private:

    std::string vectorToText(const std::vector<double>& data);


    void loadOperations();

    void applyComponentSignal(Signal &signal);

signals:

public slots:

    void execute();

    void insertData(const Signal &);
};



#endif // OUTPUTFLOW_H
