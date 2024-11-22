#include "mqttparser.h"

MQTTParser::MQTTParser(QObject *parent)
    :QObject{parent}
{


}

MQTTParser::~MQTTParser()
{

}

void MQTTParser::setPayLoad(const QByteArray &_byteArray, const QString & _topic)
{
    byteArray = _byteArray;
    topic = _topic;
}

QString MQTTParser::getTopic() const
{
    return topic;
}

QByteArray MQTTParser::getByteArray() const
{
    return byteArray;
}




