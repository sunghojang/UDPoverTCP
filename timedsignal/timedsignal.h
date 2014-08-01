// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#ifndef TIMEDSIGNAL_H
#define TIMEDSIGNAL_H

#include <QObject>
#include <QByteArray>
#include <QTimer>

class TimedSignal : public QObject
{
    Q_OBJECT

public:
    TimedSignal(QObject* parent = 0);

    void start();

signals:
    void sendData(QByteArray data);

private slots:
    void sendTrigger();

private:
    QTimer *timer;
    int i;
};


#endif // TIMEDSIGNAL_H
