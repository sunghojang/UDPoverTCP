// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTimer>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QList>
#include <QByteArray>
#include <QDataStream>

class TCPServer : public QObject
{
    Q_OBJECT

public:
    TCPServer(QObject* parent = 0);

    bool start(const quint16 &port);
    void stop();

signals:
    void connectionCount(int count);

    void info(QString sender, QString info);
    void warning(QString sender, QString warning);
    void error(QString sender, QString error);

public slots:
    void sendData(const QByteArray &data);

private slots:
    void connectClient();
    void disconnectClient();

private:
    QTcpServer *server;
    QList<QTcpSocket *> socketList;

    QString classname;
};

#endif
