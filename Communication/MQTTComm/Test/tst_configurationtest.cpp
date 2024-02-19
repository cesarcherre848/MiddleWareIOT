#include <QtTest>
#include "../MQTTCommLib/mqttcomm.h"
// add necessary includes here

class ConfigurationTest : public QObject
{
    Q_OBJECT

public:
    ConfigurationTest();
    ~ConfigurationTest();

    MQTTComm* mqttComm;

private slots:
    //void test_case1();
    void testInitConf();
    void testWait();

};

ConfigurationTest::ConfigurationTest()
{
    mqttComm = new MQTTComm();
    connect(mqttComm, &MQTTComm::updateStatusConnection, this, [=](QString status){
        qDebug() << "Status connection:" << status;
    });


}

ConfigurationTest::~ConfigurationTest()
{
    delete mqttComm;
}


void ConfigurationTest::testInitConf()
{
    mqttComm->setHostName("146.190.122.149");
    mqttComm->setPort(1883);
    mqttComm->connect();
}

void ConfigurationTest::testWait()
{
    QThread::sleep(100);
}

QTEST_APPLESS_MAIN(ConfigurationTest)

#include "tst_configurationtest.moc"
