// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include "snbgui.h"
#include "ui_snbgui.h"

SNBGui::SNBGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNBGui),
    tuStarted(0), utStarted(0)
{
    ui->setupUi(this);
    classname = "SNBGui";

    QObject::connect(&logger, SIGNAL(logUpdated(QString)), this, SLOT(updateLog(QString)));

    logger.addInfo(classname, "Started");
}

SNBGui::~SNBGui()
{
    delete ui;
}

void SNBGui::updateLog(QString log)
{
    ui->textEditLogger->setHtml(log);
}

void SNBGui::updateConnectionCount(int count)
{
    if(utStarted)
        ui->statusBar->showMessage("Connected TCP Clients: " + QString::number(count));
    else
        ui->statusBar->showMessage("");
}

void SNBGui::on_buttonUTStartStop_clicked()
{
    if(tuStarted)
    {
        logger.addError(classname, "cannot start both services simultaneously");
        return;
    }

    if(utStarted)
    {
        // Set the buttons
        ui->buttonUTStartStop->setText("Start");
        ui->tabTU->setDisabled(false);
        ui->spinBoxUdpListenPort->setDisabled(false);
        ui->spinBoxTcpServerPort->setDisabled(false);

        // Stop the services
        udpclient->disconnect();
        tcpserver->stop();

        // Delete the services
        udpclient->deleteLater();
        tcpserver->deleteLater();

        utStarted = false;
    }
    else
    {
        // Set the buttons
        ui->buttonUTStartStop->setText("Stop");
        ui->tabTU->setDisabled(true);
        ui->spinBoxUdpListenPort->setDisabled(true);
        ui->spinBoxTcpServerPort->setDisabled(true);

        // Init the services
        udpclient = new UDPClient();
        tcpserver = new TCPServer();

        QObject::connect(udpclient, SIGNAL(dataReceived(QByteArray)), tcpserver, SLOT(sendData(QByteArray)));
        QObject::connect(tcpserver, SIGNAL(connectionCount(int)), this, SLOT(updateConnectionCount(int)));

        // Connect logging
        QObject::connect(udpclient, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
        QObject::connect(udpclient, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
        QObject::connect(udpclient, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

        QObject::connect(tcpserver, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
        QObject::connect(tcpserver, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
        QObject::connect(tcpserver, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

        tcpserver->start(ui->spinBoxTcpServerPort->value());
        udpclient->connect(ui->spinBoxUdpListenPort->value());

        utStarted = true;
        updateConnectionCount(0);
    }
}

void SNBGui::on_buttonTUStartStop_clicked()
{
    if(utStarted)
    {
        logger.addError(classname, "cannot start both services simultaneously");
        return;
    }

    if(tuStarted)
    {
        // Set the buttons
        ui->buttonTUStartStop->setText("Start");
        ui->tabUT->setDisabled(false);
        ui->spinBoxUdpBroadcastPort->setDisabled(false);
        ui->spinBoxTcpClientPort->setDisabled(false);
        ui->lineEditTcpServerAddress->setDisabled(false);
        ui->statusBar->showMessage("");

        // Stop the services
        tcpclient->disconnect();
        udpserver->stop();

        // Delete the services
        tcpclient->deleteLater();
        //udpclient->deleteLater();

        tuStarted = false;
    }
    else
    {
        // Set the buttons
        ui->buttonTUStartStop->setText("Stop");
        ui->tabUT->setDisabled(true);
        ui->spinBoxUdpBroadcastPort->setDisabled(true);
        ui->spinBoxTcpClientPort->setDisabled(true);
        ui->lineEditTcpServerAddress->setDisabled(true);
        ui->statusBar->showMessage("Connected to " + ui->lineEditTcpServerAddress->text() + ":" + QString::number(ui->spinBoxTcpClientPort->value()));

        // Init the services
        tcpclient = new TCPClient();
        udpserver = new UDPServer();

        QObject::connect(tcpclient, SIGNAL(dataReceived(QByteArray)), udpserver, SLOT(sendData(QByteArray)));

        // Connect logging
        QObject::connect(tcpclient, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
        QObject::connect(tcpclient, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
        QObject::connect(tcpclient, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

        QObject::connect(udpserver, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
        QObject::connect(udpserver, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
        QObject::connect(udpserver, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

        udpserver->start(ui->spinBoxUdpBroadcastPort->value());
        tcpclient->connect(ui->lineEditTcpServerAddress->text(), ui->spinBoxTcpClientPort->value());

        tuStarted = true;
    }
}
