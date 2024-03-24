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
    explicit OutputFlow( QSettings &_settings);

    ~OutputFlow();

    void init();


private:

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");


private:





// just for test
private:

    std::string vectorToText(const std::vector<double>& data);


    void applyComponentSignal(Signal &signal);

    void initConfig();

signals:

public slots:

    void execute() override;

};



#endif // OUTPUTFLOW_H
