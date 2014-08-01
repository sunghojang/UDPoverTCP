// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UDPServer : public QObject
{
    Q_OBJECT
public:
    explicit UDPServer(QObject* parent = 0);

    bool start(const quint16 &port);
    void stop();

signals:
    void info(QString sender, QString info);
    void warning(QString sender, QString warning);
    void error(QString sender, QString error);

public slots:
    void sendData(const QByteArray &data);

private:
    qint64 port;
    QUdpSocket *udpSocket;

    QString classname;
};

#endif // SERVER_H
