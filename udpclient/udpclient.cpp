// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include "udpclient.h"

#include <QDebug>

UDPClient::UDPClient(QObject *parent) :
    QObject(parent), udpSocket(0)
{
    classname = "UDPClient";
}

bool UDPClient::connect(const qint64 &port)
{
    // Check if the socket is already initialised
    if(udpSocket)
        return false;

    // Init and connect new udpSocket
    emit info(classname, "listening to port " + QString::number(port));
    this->port = port;

    udpSocket = new QUdpSocket(this);

    QObject::connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    QObject::connect(udpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    if (!udpSocket->bind(port))
    {
        qDebug() << "bind failed";
        return false;
    }

    return true;
}

void UDPClient::disconnect()
{
    emit warning(classname, "disconnected");

    // Disconnect
    udpSocket->disconnectFromHost();
    //udpSocket->abort();

    // Reset
    udpSocket = 0;
}

void UDPClient::readData()
{
    // Now read all available datagrams from the socket
    while (udpSocket->hasPendingDatagrams()) {
        // Create a temporary buffer ...
        QByteArray data;
        data.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(data.data(), data.size());

        emit dataReceived(data);
        emit info(classname, "received data: " + QString(data));
    }
}

void UDPClient::displayError(QAbstractSocket::SocketError socketError)
{
    QString message;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        message = "QAbstractSocket::RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        message = "(QAbstractSocket::HostNotFoundError) Fortune Client. The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        message = "(QAbstractSocket::HostNotFoundError) The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
        break;
    default:
        message = "(QAbstractSocket::default) The following error occured: " + udpSocket->errorString();
    }

    emit error(classname, message);
    disconnect();
}
