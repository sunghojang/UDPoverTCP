QT       += core
QT       += network

QT       -= gui

TARGET = udpserver
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = ../build

DEFINES += UDPSERVER_LIBRARY

SOURCES += \
    udpserver.cpp

HEADERS += \
    udpserver.h
