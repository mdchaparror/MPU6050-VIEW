#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T16:57:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MPU6050-VIEW
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    qtelemento.cpp


HEADERS  += mainwindow.h \
    glwidget.h \
    qtelemento.h


FORMS    += mainwindow.ui
