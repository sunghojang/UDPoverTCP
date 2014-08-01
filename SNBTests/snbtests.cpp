// Copyright (c) 2014 All Right Reserved
//
// author  : Patrick Hanckmann
// email   : hanckmann@gmail.com
// summary :

#include "snbtests.h"
#include "ui_snbtests.h"

SNBTests::SNBTests(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNBTests),
    udpclient(0),
    started(0)
{
    ui->setupUi(this);

    classname = "SNBTest";

    QObject::connect(&logger, SIGNAL(logUpdated(QString)), this, SLOT(updateLog(QString)));

    logger.setMaxLines(100);
    logger.addInfo(classname, "Started");

    // Start listening
    on_spinBoxListenPort_valueChanged(0);
}

SNBTests::~SNBTests()
{
    delete ui;
}

void SNBTests::updateLog(QString log)
{
    ui->textEditLogger->setHtml(log);
}

void SNBTests::receivedData(QByteArray data)
{
    logger.addInfo("DATA", QString(data));
}

void SNBTests::on_spinBoxListenPort_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(udpclient)
    {
        udpclient->disconnect();
        udpclient->deleteLater();
    }

    // Start again with new port
    udpclient = new UDPClient();
    QObject::connect(udpclient, SIGNAL(dataReceived(QByteArray)), this, SLOT(receivedData(QByteArray)));

    // Connect logging
    QObject::connect(udpclient, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
    QObject::connect(udpclient, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
    QObject::connect(udpclient, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

    udpclient->connect(ui->spinBoxListenPort->value());
}

void SNBTests::on_buttonSend_clicked()
{
    // Start server and connect logging
    udpserver = new UDPServer();

    QObject::connect(udpserver, SIGNAL(info(QString,QString)), &logger, SLOT(addInfo(QString,QString)));
    QObject::connect(udpserver, SIGNAL(warning(QString,QString)), &logger, SLOT(addWarning(QString,QString)));
    QObject::connect(udpserver, SIGNAL(error(QString,QString)), &logger, SLOT(addError(QString,QString)));

    udpserver->start(ui->spinBoxBroadcastPort->value());

    // Send data
    udpserver->sendData(ui->lineEdit->text().toAscii());

    // Stop server
    udpserver->stop();
    udpserver->deleteLater();
}
