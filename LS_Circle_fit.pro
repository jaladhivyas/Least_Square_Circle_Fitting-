#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T13:04:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LS_Circle_fit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    least_square_circle.cpp

HEADERS  += mainwindow.h \
    least_square_circle.h

FORMS    += mainwindow.ui
