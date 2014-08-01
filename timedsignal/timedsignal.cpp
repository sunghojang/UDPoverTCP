// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include "timedsignal.h"

TimedSignal::TimedSignal(QObject *parent) :
    QObject(parent)
{
    i = 0;
    timer = new QTimer();
    timer->setInterval(1000);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendTrigger()));
}

void TimedSignal::start()
{
    timer->start();
}

void TimedSignal::sendTrigger()
{
    QByteArray data = QByteArray::number(i * i * i * i);
    emit sendData(data);
    ++i;
}



