#include <QtTest>
#include "datamanager.h"
#include "QSettings"
//#include "../DataManagerLib/datamanager.h"
// add necessary includes here

class DataFlow : public QObject
{
    Q_OBJECT

public:
    DataFlow();
    ~DataFlow();

    DataManager* dataManager = nullptr;

private slots:
    void test_case1();

};

DataFlow::DataFlow()
{
    QSettings _settings;
    dataManager = new DataManager(_settings);
    qDebug() << dataManager;
}

DataFlow::~DataFlow()
{
    dataManager->deleteLater();
}

void DataFlow::test_case1()
{
    //delete dataManager;

    dataManager->deleteLater();
}

QTEST_APPLESS_MAIN(DataFlow)

#include "tst_dataflow.moc"
