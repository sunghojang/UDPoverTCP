#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T16:27:36
#
#-------------------------------------------------

include(../tcpserver.pri)
include(../tcpclient.pri)
include(../udpserver.pri)
include(../udpclient.pri)

QT       += core
QT       += network

QT       -= gui

TARGET = snb
CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = ../build

TEMPLATE = app

SOURCES += main.cpp
