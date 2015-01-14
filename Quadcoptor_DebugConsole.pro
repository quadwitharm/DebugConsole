#-------------------------------------------------
#
# Project created by QtCreator 2015-01-13T17:28:52
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quadcoptor_DebugConsole
TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    serial.cpp \
    terminal.cpp \
    inputprocessor.cpp \
    commandsender.cpp \
    signalline.cpp

HEADERS  += mainwindow.h \
    ../qcustomplot/qcustomplot.h \
	qcustomplot.h \
    serial.h \
    terminal.h \
    inputprocessor.h \
    commandsender.h \
    signalline.h

FORMS    += mainwindow.ui
