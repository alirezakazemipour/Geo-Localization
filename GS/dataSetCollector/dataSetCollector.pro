#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T11:11:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataSetCollector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h


LIBS += `pkg-config opencv --libs`
