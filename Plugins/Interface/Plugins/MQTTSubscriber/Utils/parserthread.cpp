#include "parserthread.h"

ParserThread::ParserThread(MQTTParser *_parser, QObject *parent)
    :  QThread{parent}, parser(_parser)
{

}

ParserThread::~ParserThread()
{
    if (isRunning()){
        quit();
    }
    wait();
}

MQTTParser *ParserThread::getParser() const
{
    return parser;
}

void ParserThread::run()
{
    if(parser){
        parser->execute();
    }
}
