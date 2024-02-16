#include <QtTest>
//#include "../DataManagerLib/datamanager.h"
// add necessary includes here

class DataFlow : public QObject
{
    Q_OBJECT

public:
    DataFlow();
    ~DataFlow();

    //DataManager* dataManager;
private slots:
    void test_case1();

};

DataFlow::DataFlow()
{
    //dataManager = new DataManager();
}

DataFlow::~DataFlow()
{

}

void DataFlow::test_case1()
{
    //delete dataManager;
}

QTEST_APPLESS_MAIN(DataFlow)

#include "tst_dataflow.moc"
