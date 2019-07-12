#-------------------------------------------------
#
# Project created by QtCreator 2019-02-18T17:51:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = autcup2019
TEMPLATE = app



CONFIG += c++11
CONFIG += extserialport
 QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    capture.cpp \
    programhandeler.cpp \
    inverter.cpp \
    lineEquations.cpp \
    qr_reciever.cpp \
    handler.cpp \
    colordetection.cpp \
    udetection.cpp \
    optflow.cpp \
    quad_board.cpp \
    hdetection.cpp

HEADERS  += mainwindow.h \
    capture.h \
    includes.h \
    programhandeler.h \
    inverter.h \
    lineEquations.h \
    qr_reciever.h \
    handler.h \
    colordetection.h \
    udetection.h \
    optflow.h \
    quad_board.h \
    hdetection.h


LIBS += `pkg-config opencv --libs`

LIBS+=-lzbar
#include(/home/kimia/qextserialport-master/src/qextserialport.pri)
