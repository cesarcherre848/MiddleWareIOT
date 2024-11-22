#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <QObject>
#include "../Models/confDispatcher.h"

class EventParser : public QObject
{
    Q_OBJECT
public:
    explicit EventParser(QObject *parent = nullptr);
    ~EventParser();

    void setPayLoad(const QByteArray &byteArray, QString topic);


private:

    QByteArray byteArray;
    QString topic;


public slots:

    void execute();

signals:

    void finished();

    void updateAction(ActionUpdate);

};

#endif // EVENTPARSER_H
