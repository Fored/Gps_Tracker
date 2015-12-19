#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T16:07:37
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GpsTracker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlite3.c

HEADERS  += mainwindow.h \
    sqlite3.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY += location
QT += positioning
