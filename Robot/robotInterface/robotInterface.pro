#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T10:01:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotInterface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capture.cpp \
    optflow.cpp \
    quad_board.cpp \
    sendimg.cpp \
    getposition.cpp

HEADERS  += mainwindow.h \
    capture.h \
    optflow.h \
    quad_board.h \
    sendimg.h \
    getposition.h

DISTFILES += \
    robotInterface.pro.user \
    Makefile

LIBS += `pkg-config opencv --libs`

