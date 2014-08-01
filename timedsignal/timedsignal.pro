QT       += core

QT       -= gui

TARGET = timedsignal
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = ../build

DEFINES += TIMEDSIGNAL_LIBRARY

SOURCES += \
    timedsignal.cpp

HEADERS += \
    timedsignal.h
