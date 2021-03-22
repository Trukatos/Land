#-------------------------------------------------
#
# Project created by QtCreator 2014-01-26T10:37:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LandmassDetectorGUI
TEMPLATE = app


SOURCES += main.cpp\
        landmassdetector.cpp \
    dialog.cpp

HEADERS  += landmassdetector.h \
    Landmass.h \
    dialog.h

FORMS    += landmassdetector.ui \
    dialog.ui

CONFIG += c++11

