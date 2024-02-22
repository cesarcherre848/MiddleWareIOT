#ifndef PARSERTHREAD_H
#define PARSERTHREAD_H

#include <QObject>
#include <QThread>
#include "mqttparser.h"

class ParserThread : public QThread
{
    Q_OBJECT
public:
    explicit ParserThread(MQTTParser* _parser, QObject *parent = nullptr);
    ~ParserThread();

    MQTTParser *getParser() const;

private:
    MQTTParser* parser;

protected:

    void run() override;
signals:
};

#endif // PARSERTHREAD_H
