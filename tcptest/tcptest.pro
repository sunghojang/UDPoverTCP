#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T16:33:17
#
#-------------------------------------------------

include(../tcpclient.pri)
include(../tcpserver.pri)
include(../timedsignal.pri)

QT       += core
QT       += network

QT       -= gui

TARGET = tcptest
CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = ../build

TEMPLATE = app


SOURCES += main.cpp
