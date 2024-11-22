#include <QtTest>
#include "../PayloadErbessdLib/payloaderbessd.h"
#include "QMap"
// add necessary includes here

class DataParse : public QObject
{
    Q_OBJECT

public:
    DataParse();
    ~DataParse();

    PayloadErbessd* parser;

private slots:
    void test_case1();
    void readJsonFile();

};

DataParse::DataParse()
{
    QMap<QString, QString> mapIdComponent;
    parser = new PayloadErbessd();
}

DataParse::~DataParse()
{
    delete parser;
}

void DataParse::test_case1()
{

}

void DataParse::readJsonFile()
{
    QString filePath = "D:/Proyectos/Health Vibration Monitoring/Dinamic Libraries/DataParsers/PayloadErbessd/Test/collection.json";
    QFile file(filePath);

    // Verificar si el archivo se puede abrir para lectura
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << file.errorString();
        return;
        //return QJsonObject(); // Devolver un objeto JSON vacío si no se pudo abrir el archivo
    }

    QByteArray byteArray = file.readAll();
    file.close();

    parser->setPayLoad(byteArray, "");
}

QTEST_APPLESS_MAIN(DataParse)

#include "tst_dataparse.moc"
