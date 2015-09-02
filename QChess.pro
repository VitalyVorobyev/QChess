#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T23:42:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QChess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qposition.cpp \
    qbitboard.cpp \
    qmagichash.cpp

HEADERS  += mainwindow.h \
    qposition.h \
    qbitboard.h \
    qmagichash.h \
    qlookup.h

FORMS    += mainwindow.ui
