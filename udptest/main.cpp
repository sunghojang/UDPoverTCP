// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include <QCoreApplication>
#include <QObject>

#include "udpserver.h"
#include "udpclient.h"

#include "timedsignal.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qint64 udpport = 55555;

    UDPServer us;
    UDPClient uc;

    TimedSignal timer;

    QObject::connect(&timer, SIGNAL(sendData(QByteArray)), &us, SLOT(sendData(QByteArray)));

    us.start(udpport);
    uc.connect(udpport);

    timer.start();

    return a.exec();
}
