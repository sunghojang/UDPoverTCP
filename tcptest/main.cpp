// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include <QCoreApplication>
#include <QObject>

#include "tcpserver.h"
#include "tcpclient.h"

#include "timedsignal.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qint64 tcpport = 55555;
    QString host   = "127.0.0.1";

    TCPServer ts;
    TCPClient tc;

    TimedSignal timer;

    QObject::connect(&timer, SIGNAL(sendData(QByteArray)), &ts, SLOT(sendData(QByteArray)));

    ts.start(tcpport);
    tc.connect(host, tcpport);

    timer.start();

    return a.exec();
}
