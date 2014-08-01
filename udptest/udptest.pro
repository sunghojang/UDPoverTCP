#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T16:33:27
#
#-------------------------------------------------

include(../udpclient.pri)
include(../udpserver.pri)
include(../timedsignal.pri)

QT       += core
QT       += network

QT       -= gui

TARGET = udptest
CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = ../build

TEMPLATE = app


SOURCES += main.cpp
