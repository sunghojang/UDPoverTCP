// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#ifndef SNBGUI_H
#define SNBGUI_H

#include <QMainWindow>
#include <QString>

#include "htmllogger.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "udpclient.h"
#include "udpserver.h"

namespace Ui {
class SNBGui;
}

class SNBGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit SNBGui(QWidget *parent = 0);
    ~SNBGui();

private slots:
    void updateLog(QString log);
    void updateConnectionCount(int count);

    void on_buttonUTStartStop_clicked();
    void on_buttonTUStartStop_clicked();

private:
    Ui::SNBGui *ui;
    HTMLLogger logger;

    TCPClient *tcpclient;
    TCPServer *tcpserver;
    UDPClient *udpclient;
    UDPServer *udpserver;

    bool tuStarted;
    bool utStarted;

    QString classname;
};

#endif // SNBGUI_H
