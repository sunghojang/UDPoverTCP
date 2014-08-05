// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include <QBuffer>
#include <QDataStream>

#include "tcpserver.h"

static inline QByteArray IntToArray(qint16 source);

TCPServer::TCPServer(QObject *parent)
    : QObject(parent), server(0)
{
    classname = "TCPServer";
}

bool TCPServer::start(const quint16 &port)
{
    if(server)
        return false;

    emit info(classname, "started at port " + QString::number(port));

    server = new QTcpServer(this);
    bool result1 = QObject::connect(server, SIGNAL(newConnection()), this, SLOT(connectClient()));
    bool result2 = server->listen(QHostAddress::Any, port);

    if (!result1)
        emit error(classname, "TCP server could not connect newConnection");
    if (!result2)
        emit error(classname, "TCP server failed to start listening");

    return (result1 && result2);
}

void TCPServer::stop()
{
    if(!server)
        return;

    emit warning(classname, "stopped");

    server->close();
    server->deleteLater();
    server = 0;
}

void TCPServer::sendData(const QByteArray &data)
{
    if (!server)
        return;

    // Do nothing if there are no active connections
    if (socketList.size() <= 0)
        return;

    // Build and send the package
    QByteArray header = "TNO";
    for(int i = 0; i < socketList.size(); ++i)
    {
        socketList.at(i)->write(header);
        socketList.at(i)->write(IntToArray((quint16) data.size()));
        socketList.at(i)->write(data);
        if (!socketList.at(i)->flush())
            emit warning(classname, "TCP server socket flush failed");
        emit info(classname, "send data: " + QString(data));
    }
}

void TCPServer::clientDataReceived(const QByteArray &data)
{
    emit dataReceived(data);
}

void TCPServer::connectClient()
{
    emit info(classname, "adding new connection");
    while(server->hasPendingConnections())
    {
        QTcpSocket *socket = server->nextPendingConnection();
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectClient()));
        socketList.append(socket);
    }

    emit connectionCount(socketList.size());
}

void TCPServer::disconnectClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();

    // TODO: This should be done more efficient
    int removed = 0;
    for(int i = 0; i < socketList.size(); ++i)
    {
        if (socketList.at(i) == socket)
        {
            socket->deleteLater();
            socketList.removeAt(i);
            removed++;
        }
    }

    if(removed != 1)
        emit error(classname, "problem removing connection, count: " + QString::number(removed));

    emit connectionCount(socketList.size());
}

void TCPServer::clientInfo(const QString &sender, const QString &message)
{
    emit info(classname + "->" + sender, message);
}

void TCPServer::clientWarning(const QString &sender, const QString &message)
{
    emit warning(classname + "->" + sender, message);
}

void TCPServer::clientError(const QString &sender, const QString &message)
{
    emit error(classname + "->" + sender, message);
}

QByteArray IntToArray(qint16 source) // Use qint16 to ensure that the number have 2 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
