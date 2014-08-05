// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include <QCoreApplication>
#include <QObject>

#include "tcpserver.h"
#include "tcpclient.h"
#include "udpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qint64 udpport = 50000;
    qint64 tcpport = 55555;
    QString host   = "127.0.0.1";

    // Side one
    UDPClient uc;
    TCPServer ts;

    QObject::connect(&uc, SIGNAL(dataReceived(QByteArray)), &ts, SLOT(sendData(QByteArray)));

    ts.start(tcpport);
    uc.connect(udpport);


    // Side two
    TCPClient tc;
    //UDPServer us;

    //QObject::connect(&tc, SIGNAL(dataReceived(QByteArray)), &us, SLOT(sendData(QByteArray)));

    //us.start(udpport);
    tc.connect(host, tcpport);

    return a.exec();
}
