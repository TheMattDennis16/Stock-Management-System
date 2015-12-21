#-------------------------------------------------
#
# Project created by QtCreator 2015-04-06T19:38:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maintenance
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Catalogue.cpp \
    FileHandling.cpp \
    Footwear.cpp

HEADERS  += MainWindow.h \
    Catalogue.h \
    FileHandling.h \
    Footwear.h

FORMS    += MainWindow.ui
