// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include "udpserver.h"

UDPServer::UDPServer(QObject *parent) :
    QObject(parent), udpSocket(0)
{
    classname = "UDPServer";
}

bool UDPServer::start(const quint16 &port)
{
    if (udpSocket)
        return false;

    emit info(classname, "started");

    this->port = port;
    udpSocket = new QUdpSocket(this);

    return true;
}

void UDPServer::stop()
{
    if (!udpSocket)
        return;

    emit warning(classname, "stopped");

    udpSocket->deleteLater();
    udpSocket = 0;
}

void UDPServer::sendData(const QByteArray &data)
{
    if (!udpSocket)
        return;

    udpSocket->writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, port);
    udpSocket->flush();

    emit info(classname, "send data: " + QString(data));
}
