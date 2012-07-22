#-------------------------------------------------
#
# Project created by QtCreator 2012-07-09T18:32:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlameCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    flame.cpp \
    function.cpp

HEADERS  += mainwindow.h \
    flame.h \
    function.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Idées.txt
